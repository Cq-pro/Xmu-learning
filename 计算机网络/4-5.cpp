#include <stdio.h>
#include <pcap.h>
#include <stdint.h>

#define ETHERTYPE_IP 0x0800
#define ETHERTYPE_ARP 0x0806
#define ETHERTYPE_IPV6 0x86DD
#define IPPROTO_TCP 6
#define TCP_FLAG_SYN 0x02
#define TCP_FLAG_ACK 0x10
#define TCP_FLAG_FIN 0x01

typedef struct ether_header {
    uint8_t ether_dhost[6];
    uint8_t ether_shost[6];
    uint16_t ether_type;
} ether_header;

typedef struct ip_header {
    uint8_t ip_vhl;
    uint8_t ip_tos;
    uint16_t ip_len;
    uint16_t ip_id;
    uint16_t ip_off;
    uint8_t ip_ttl;
    uint8_t ip_p;
    uint16_t ip_sum;
    uint32_t ip_src;
    uint32_t ip_dst;
} ip_header;

typedef struct tcp_header {
    uint16_t th_sport;
    uint16_t th_dport;
    uint32_t th_seq;
    uint32_t th_ack;
    uint8_t th_offx2;
    uint8_t th_flags;
    uint16_t th_win;
    uint16_t th_sum;
    uint16_t th_urp;
} tcp_header;

void packet_handler(u_char* user_args, const struct pcap_pkthdr* pkt_header, const u_char* pkt_data) {
    ether_header* eth_hdr = (ether_header*)pkt_data;
    if (eth_hdr->ether_type == htons(ETHERTYPE_IP)) {
        ip_header* ip_hdr = (ip_header*)(pkt_data + sizeof(ether_header));
        if (ip_hdr->ip_p == IPPROTO_TCP) {
            tcp_header* tcp_hdr = (tcp_header*)(pkt_data + sizeof(ether_header) + (ip_hdr->ip_vhl & 0x0F) * 4);
            uint16_t src_port = ntohs(tcp_hdr->th_sport);
            uint16_t dst_port = ntohs(tcp_hdr->th_dport);
            printf("Source Port: %u, Destination Port: %u\n", src_port, dst_port);

            // 判断是否是握手包
            if (tcp_hdr->th_flags & TCP_FLAG_SYN && !(tcp_hdr->th_flags & TCP_FLAG_ACK)) {
                static int syn_count = 0;
                printf("握手包 %d\n", ++syn_count);
            }

            // 判断是否是挥手包
            if (tcp_hdr->th_flags & TCP_FLAG_FIN && tcp_hdr->th_flags & TCP_FLAG_ACK) {
                static int fin_count = 0;
                printf("挥手包 %d\n", ++fin_count);
            }
        }
    }
}

int main() {
    pcap_t* handle = NULL;
    char errbuf[PCAP_ERRBUF_SIZE];

    // 打开适配器进行捕获
    handle = pcap_open_live("\\Device\\NPF_{选择适配器}", BUFSIZ, 1, 1000, errbuf); // 选择你的适配器
    if (handle == NULL) {
        fprintf(stderr, "Error opening adapter: %s\n", errbuf);
        return -1;
    }

    // 开始捕获数据包
    pcap_loop(handle, 0, packet_handler, NULL);

    // 关闭捕获会话
    pcap_close(handle);

    return 0;
}
