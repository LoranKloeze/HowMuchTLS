/*
HowMuchTLS
Simple program to check the amount of port 80 traffic compared to port 443 traffic
20-06-2017
(c) 2017 - Loran Kloeze - loran@ralon.nl

https://github.com/LoranKloeze/WhatsAllApp

*/

#pragma once

#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>

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
