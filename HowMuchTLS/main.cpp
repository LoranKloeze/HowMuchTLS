/*
HowMuchTLS
Simple program to check the amount of port 80 traffic compared to port 443 traffic
20-06-2017
(c) 2017 - Loran Kloeze - loran@ralon.nl

https://github.com/LoranKloeze/WhatsAllApp

*/

#include "HowMuchTLS.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	HowMuchTLS w;
	w.show();
	return a.exec();
}
