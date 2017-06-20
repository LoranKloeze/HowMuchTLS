/*
HowMuchTLS
Simple program to check the amount of port 80 traffic compared to port 443 traffic
20-06-2017
(c) 2017 - Loran Kloeze - loran@ralon.nl

https://github.com/LoranKloeze/WhatsAllApp

*/

#pragma once
#include <QThread>
#include "pcap.h"
class TapThread : public QThread
{
	Q_OBJECT
		void TapThread::run() override;

public:
	static friend void processPacket(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data);
	TapThread(const QString &s);

private:
	pcap_t *tapInterface;
	QString selectedInterfaceName;

signals:
	void packetReceived(int dstPortNr);

};

