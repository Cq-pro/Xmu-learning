#include <iostream>
#define _CRT_SECURE_NO_WARNINGS
#include <pcap.h>

int main() {
    pcap_if_t* alldevs;
    char errbuf[PCAP_ERRBUF_SIZE];

    // 获取网卡设备列表
    if (pcap_findalldevs(&alldevs, errbuf) == -1) {
        std::cerr << "Error in pcap_findalldevs: " << errbuf << std::endl;
        return 1;
    }

    int i = 0;
    // 遍历网卡设备列表并打印信息
    for (pcap_if_t* d = alldevs; d != NULL; d = d->next) {
        std::cout << ++i << ". " << d->name;
        if (d->description)
            std::cout << " (" << d->description << ")";
        std::cout << std::endl;
    }

    // 释放网卡设备列表
    pcap_freealldevs(alldevs);

    return 0;
}
