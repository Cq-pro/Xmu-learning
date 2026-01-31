#define WIN32
#include<iostream>
#include<sstream>
#include<string>
#include<map>
#include<fstream>
#include <pcap.h>
#include<vector>
#include <iomanip>
#pragma warning(disable:4996)
using namespace std;
map<string, string[3]> ftp;
bool flag;

typedef struct mac_header
{
	u_char dest_addr[6];
	u_char src_addr[6];
	u_char type[2];
} mac_header;

/* IPv4 首部 ,20字节*/
typedef struct ip_header {
	u_char  ver_ihl;        // 版本 (4 bits) + 首部长度 (4 bits)  
	u_char  tos;            // 服务类型(Type of service)  
	u_short tlen;           // 总长(Total length)  
	u_short identification; // 标识(Identification)  
	u_short flags_fo;       // 标志位(Flags) (3 bits) + 段偏移量(Fragment offset) (13 bits)  
	u_char  ttl;            // 存活时间(Time to live)  
	u_char  proto;          // 协议(Protocol)  
	u_short crc;            // 首部校验和(Header checksum)  
	u_char  saddr[4];      // 源地址(Source address)  
	u_char  daddr[4];      // 目的地址(Destination address)  
	u_int   op_pad;         // 选项与填充(Option + Padding)  
}ip_header;
//TCP头部，总长度20字节  
typedef struct tcp_header
{
	u_short sport;            //源端口号  
	u_short dport;             //目的端口号  
	u_int th_seq;                //序列号  
	u_int th_ack;               //确认号  
	u_int th1 : 4;              //tcp头部长度  
	u_int th_res : 4;             //6位中的4位首部长度  
	u_int th_res2 : 2;            //6位中的2位首部长度  
	u_char th_flags;            //6位标志位  
	u_short th_win;             //16位窗口大小  
	u_short th_sum;             //16位tcp检验和  
	u_short th_urp;             //16位紧急指针  
}tcp_header;

/* 回调函数原型 */
void packet_handler(u_char* param, const struct pcap_pkthdr* header, const u_char* pkt_data);
string get_request_m_ip_message(const u_char* pkt_data);
string get_response_m_ip_message(const u_char* pkt_data);
void print(const struct pcap_pkthdr* header, string m_ip_message, const u_char* pkt_data);

int main()
{
	flag = false;
	pcap_if_t* alldevs;
	pcap_if_t* d;
	int inum;
	int i = 0;
	pcap_t* adhandle;
	char errbuf[PCAP_ERRBUF_SIZE];
	u_int netmask;
	char packet_filter[] = "tcp port 21";
	struct bpf_program fcode;

	/* 获得设备列表 */
	if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, &alldevs, errbuf) == -1)
	{
		fprintf(stderr, "Error in pcap_findalldevs: %s\n", errbuf);
		exit(1);
	}

	/* 打印列表 */
	for (d = alldevs; d; d = d->next)
	{
		printf("%d. %s", ++i, d->name);
		if (d->description)
			printf(" (%s)\n", d->description);
		else
			printf(" (No description available)\n");
	}

	if (i == 0)
	{
		printf("\nNo interfaces found! Make sure WinPcap is installed.\n");
		return -1;
	}

	printf("Enter the interface number (1-%d):", i);
	cin >> inum;

	if (inum < 1 || inum > i)
	{
		printf("\nInterface number out of range.\n");
		/* 释放设备列表 */
		pcap_freealldevs(alldevs);
		return -1;
	}

	/* 跳转到已选设备 */
	for (d = alldevs, i = 0; i < inum - 1; d = d->next, i++);

	/* 打开适配器 */
	if ((adhandle = pcap_open(d->name,  // 设备名  
		65536,     // 要捕捉的数据包的部分  
		// 65535保证能捕获到不同数据链路层上的每个数据包的全部内容  
		PCAP_OPENFLAG_PROMISCUOUS,         // 混杂模式  
		1000,      // 读取超时时间  
		NULL,      // 远程机器验证  
		errbuf     // 错误缓冲池  
	)) == NULL)
	{
		fprintf(stderr, "\nUnable to open the adapter. %s is not supported by WinPcap\n", d->name);
		/* 释放设备列表 */
		pcap_freealldevs(alldevs);
		return -1;
	}

	/* 检查数据链路层，为了简单，我们只考虑以太网 */
	if (pcap_datalink(adhandle) != DLT_EN10MB)
	{
		fprintf(stderr, "\nThis program works only on Ethernet networks.\n");
		/* 释放设备列表 */
		pcap_freealldevs(alldevs);
		return -1;
	}

	if (d->addresses != NULL)
		/* 获得接口第一个地址的掩码 */
		netmask = ((struct sockaddr_in*)(d->addresses->netmask))->sin_addr.S_un.S_addr;
	else
		/* 如果接口没有地址，那么我们假设一个C类的掩码 */
		netmask = 0xffffff;


	//编译过滤器  
	if (pcap_compile(adhandle, &fcode, packet_filter, 1, netmask) < 0)
	{
		fprintf(stderr, "\nUnable to compile the packet filter. Check the syntax.\n");
		/* 释放设备列表 */
		pcap_freealldevs(alldevs);
		return -1;
	}

	//设置过滤器  
	if (pcap_setfilter(adhandle, &fcode) < 0)
	{
		fprintf(stderr, "\nError setting the filter.\n");
		/* 释放设备列表 */
		pcap_freealldevs(alldevs);
		return -1;
	}

	printf("\nlistening on %s...\n", d->description);

	/* 释放设备列表 */
	pcap_freealldevs(alldevs);

	/* 开始捕捉 */
	pcap_loop(adhandle, 0, packet_handler, NULL);
	
	return 0;
}


static int cnt = 0;
void print_packet_content(const u_char* packet_data, int packet_length) {
	// Iterate over the packet data and print each byte as hexadecimal
	for (int i = 0; i < packet_length; ++i) {
		printf("%02X ", packet_data[i]);
		// Print a newline after every 16 bytes for better readability
		if ((i + 1) % 16 == 0) {
			printf("\n");
		}
	}
	printf("\n");
}
vector<std::string> parse_ftp_arguments(const std::string& command) {
	std::vector<std::string> arguments;
	std::istringstream iss(command);
	std::string argument;
	while (std::getline(iss, argument, ' ')) {
		arguments.push_back(argument);
	}
	return arguments;
}

string parse_ftp_command(const std::vector<char>& data) {
	std::string command;
	for (char ch : data) {
		if (ch == '\r' || ch == '\n') {
			break;
		}
		command.push_back(ch);
	}
	return command;
}
// 将十六进制字符串转换为ASCII字符串
string hex_to_ascii(const string& hex_string) {
	string ascii_string;
	for (size_t i = 0; i < hex_string.length(); i += 2) {
		string byte = hex_string.substr(i, 2);
		char chr = (char)stoi(byte, nullptr, 16);
		ascii_string.push_back(chr);
	}
	return ascii_string;
}

void packet_handler(u_char* param, const struct pcap_pkthdr* header, const u_char* pkt_data)
{
	int packet_length = header->len;

	// 提取各个字段
	stringstream hex_data_stream;
	hex_data_stream << std::hex;
	for (int i = 0; i < packet_length; ++i) {
		hex_data_stream << std::setw(2) << std::setfill('0') << static_cast<int>(pkt_data[i]);
	}
	string hex_data = hex_data_stream.str();

	string src_addr = "";
	string dest_addr = "";
	string flags_str = hex_data.substr(24, 2);
	string ftp_command = "";

	// 解析源地址
	for (int i = 0; i < 8; i += 2) {
		src_addr += to_string(std::stoi(hex_data.substr(i, 2), nullptr, 16));
		if (i < 6) src_addr += ".";
	}

	// 解析目的地址
	for (int i = 8; i < 16; i += 2) {
		dest_addr += to_string(stoi(hex_data.substr(i, 2), nullptr, 16));
		if (i < 14) dest_addr += ".";
	}

	// 解析标志位
	int flags = stoi(flags_str, nullptr, 16);
	int urg_flag = (flags >> 5) & 1;
	int ack_flag = (flags >> 4) & 1;
	int psh_flag = (flags >> 3) & 1;
	int rst_flag = (flags >> 2) & 1;
	int syn_flag = (flags >> 1) & 1;
	int fin_flag = flags & 1;

	// 查找FTP命令的起始位置
	size_t ftp_command_start = hex_data.find("0d0a") + 4; // FTP命令通常以0D0A（CRLF）作为结束标志，因此在此之后即为FTP命令

	// 提取FTP命令
	if (ftp_command_start != string::npos) {
		// 查找FTP命令的结束位置（空格）
		size_t ftp_command_end = hex_data.find("20", ftp_command_start); // 20是空格的ASCII码
		if (ftp_command_end != string::npos) {
			ftp_command = hex_data.substr(ftp_command_start, ftp_command_end - ftp_command_start);
		}
		else {
			// 如果没有找到空格，则直接取FTP命令直到行尾
			ftp_command = hex_data.substr(ftp_command_start);
		}
		// 将十六进制的FTP命令转换为ASCII字符
		ftp_command = hex_to_ascii(ftp_command);
	}
	else {
		// 如果没有找到CRLF，则提示未找到FTP命令
		ftp_command = "未找到FTP命令";
	}

	// 显示解析结果
	cout << "源地址: " << src_addr << endl;
	cout << "目的地址: " << dest_addr << endl;
	cout << "标志位：" << endl;
	cout << "URG: " << urg_flag << " ACK: " << ack_flag << " PSH: " << psh_flag << " RST: " << rst_flag << " SYN: " << syn_flag << " FIN: " << fin_flag << std::endl;
	cout << "FTP Command: " << ftp_command << endl;
	cout << endl;
}
