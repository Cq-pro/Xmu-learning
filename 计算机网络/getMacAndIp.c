#define WIN32      // 必须加这条，否则vs不会自动识别
#include <stdio.h>
#include <pcap.h>
#pragma comment(lib, "wpcap.lib")

main()
{
	pcap_if_t* alldevs, * d;
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
	pcap_freealldevs(alldevs);
}
