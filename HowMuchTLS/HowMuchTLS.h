#pragma once

#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QTimer>
#include <qmath.h>
#include "pcap.h"

QT_CHARTS_USE_NAMESPACE

class HowMuchTLS : public QMainWindow
{
	Q_OBJECT

public:
	HowMuchTLS(QWidget *parent = Q_NULLPTR);

private:
	QPieSlice *pieSliceSecure;
	QPieSlice *pieSliceInsecure;
	ulong securePacketsReceived = 0;
	ulong insecurePacketsReceived = 0;

	void startUiRefresher();
	QChartView * createChart();
	void startScan();

public slots:
	void processPacket(int dstPortNr);
};
