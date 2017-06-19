#include "HowMuchTLS.h"
#include "TapThread.h"

HowMuchTLS::HowMuchTLS(QWidget *parent)
	: QMainWindow(parent)
{
	setMinimumWidth(450);
	setMinimumHeight(450);
	setCentralWidget(createChart());
	startScan();
	startUiRefresher();
}

void HowMuchTLS::startUiRefresher()
{
	QTimer *timer = new QTimer(this);
	connect(timer, &QTimer::timeout,
		[=]() {
		qreal totalPackets = insecurePacketsReceived + securePacketsReceived;
		if (totalPackets > 0) {
			pieSliceInsecure->setValue(insecurePacketsReceived);
			qreal q = (insecurePacketsReceived / totalPackets) * 100;
			int insecurePart = qCeil(insecurePacketsReceived / totalPackets * 100);
			pieSliceInsecure->setLabel(QString("Port 80 (%1%)").arg(insecurePart));

			pieSliceSecure->setValue(securePacketsReceived);
			int securePart = 100 - insecurePart;
			pieSliceSecure->setLabel(QString("Port 443 (%1%)").arg(securePart));
		}
		
	});
	timer->start(1000);
}

QChartView * HowMuchTLS::createChart()
{
	QChart *pieChart = new QChart();
	QChartView *chartView = new QChartView(pieChart);
	QPieSeries *pieChartSeries = new QPieSeries();
	QBrush brushSecure(QColor::fromRgb(15, 162, 74));
	QColor colorSecureOutline = QColor::fromRgb(0, 104, 44);
	QBrush brushInsecure(QColor::fromRgb(238, 45, 36));
	QColor colorInsecureOutline = QColor::fromRgb(143,19,6);
	int borderWidth = 3;
	pieSliceSecure = new QPieSlice("Port 443 (50%)", 1);
	pieSliceInsecure = new QPieSlice("Port 80 (50%)", 1);

	pieSliceSecure->setBrush(brushSecure);
	pieSliceSecure->setBorderColor(colorSecureOutline);
	pieSliceSecure->setBorderWidth(borderWidth);
	pieChartSeries->append(pieSliceSecure);

	pieSliceInsecure->setBrush(brushInsecure);
	pieSliceInsecure->setBorderColor(colorInsecureOutline);
	pieSliceInsecure->setBorderWidth(borderWidth);
	pieChartSeries->append(pieSliceInsecure);

	pieChart->addSeries(pieChartSeries);
	chartView->setRenderHint(QPainter::Antialiasing);

	return chartView;
}

void HowMuchTLS::startScan()
{
	pcap_if_t *alldevs, *iface;
	pcap_findalldevs(&alldevs, NULL);
	for (iface = alldevs; iface; iface = iface->next) {
		TapThread *t = new TapThread(iface->name);
		QObject::connect(t, &TapThread::packetReceived, this, &HowMuchTLS::processPacket);
		t->start();
	}
	pcap_freealldevs(alldevs);
	pcap_freealldevs(iface);
}

void HowMuchTLS::processPacket(int dstPortNr)
{
	switch (dstPortNr)
	{
	case 80:
		insecurePacketsReceived++;
		break;
	case 443:
		securePacketsReceived++;
		break;
	default:
		break;
	}

}