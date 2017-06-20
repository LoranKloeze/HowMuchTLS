#include "TapThread.h"

// Run pcap on the network interface
void TapThread::run() {
	char errBuf[PCAP_ERRBUF_SIZE];
	bpf_program bp;
	char filterText[] = "(ip and dst port 443) or (ip and dst port 80)";

	int status = 0;
	tapInterface = pcap_open_live(selectedInterfaceName.toStdString().c_str(),
		65536,
		1,
		1000,
		errBuf);

	pcap_compile(tapInterface, &bp, filterText, 0, 0);
	pcap_setfilter(tapInterface, &bp);

	while ((status = pcap_dispatch(tapInterface, -1, processPacket, (u_char*)this)) > -1);

}

// Initialize TapThread with the network interface name
TapThread::TapThread(const QString &s)
{
	selectedInterfaceName = s;
}

// When a packet is received, signal the main thread
void processPacket(u_char * param, const pcap_pkthdr * header, const u_char * pkt_data)
{
	TapThread *t = (TapThread*)param;
	int dstPortNr = pkt_data[37] | pkt_data[36] << 8;
	emit t->packetReceived(dstPortNr);
}
