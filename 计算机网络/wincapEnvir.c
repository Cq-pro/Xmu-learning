#define WIN32      // 必须加这条，否则vs不会自动识别
#include <stdio.h>
#include <pcap.h>
#pragma comment(lib, "wpcap.lib")
#define ETHER_ADDR_LEN 6

struct ether_header {
	u_char ether_dhost[ETHER_ADDR_LEN]; /* 目的MAC地址 */
	u_char ether_shost[ETHER_ADDR_LEN]; /* 源MAC地址 */
	u_short ether_type; /* 以太网帧类型 */
};

void packet_handler(u_char* user, const struct pcap_pkthdr* pkthdr, const u_char* packet) {
	struct ether_header* eth_header;

	eth_header = (struct ether_header*)packet;

	// 解析出目的MAC地址
	printf("Destination MAC Address: %02X:%02X:%02X:%02X:%02X:%02X\n",
		eth_header->ether_dhost[0], eth_header->ether_dhost[1],
		eth_header->ether_dhost[2], eth_header->ether_dhost[3],
		eth_header->ether_dhost[4], eth_header->ether_dhost[5]);

	// 解析出源MAC地址
	printf("Source MAC Address: %02X:%02X:%02X:%02X:%02X:%02X\n",
		eth_header->ether_shost[0], eth_header->ether_shost[1],
		eth_header->ether_shost[2], eth_header->ether_shost[3],
		eth_header->ether_shost[4], eth_header->ether_shost[5]);
}


main()
{
	//在控制台打印出网卡的基础设备列表
	/*pcap_if_t* alldevs, * d;
	int i = 0;
	char errbuf[PCAP_ERRBUF_SIZE];
	if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL,
		&alldevs, errbuf) == -1)
	{
		fprintf(stderr, "Error in pcap_findalldevs_ex: %s\n",
			errbuf);
		exit(1);
	}
	for (d = alldevs; d != NULL; d = d->next)
	{
		printf("%d.%s", ++i, d->name);
		if (d->description)
		{
			printf("(%s)\n", d->description);
		}
		else {
			printf("(No description available)\n");
		}
	}
	if (i == 0)
	{
		printf("\nNo interfaces found! Make sure Winpcap is installed.\n");
		return;
	}
	// 释放设备
	pcap_freealldevs(alldevs);*/
	pcap_t* handle;
	char errbuf[PCAP_ERRBUF_SIZE];
	struct pcap_pkthdr header;
	const u_char* packet;

	// 打开网络接口进行捕获
	handle = pcap_open_live("WLAN", BUFSIZ, 1, 1000, errbuf);
	if (handle == NULL) {
		fprintf(stderr, "Couldn't open device: %s\n", errbuf);
		return 1;
	}

	// 开始捕获数据包并调用处理函数
	pcap_loop(handle, 0, packet_handler, NULL);

	// 关闭捕获会话
	pcap_close(handle);

	return 0;
}
