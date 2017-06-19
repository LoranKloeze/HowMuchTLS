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

