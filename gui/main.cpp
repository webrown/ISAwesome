#include <QApplication>
#include <stdio.h>
#include "ui_pisa.h"
#include <QFont>
#include <QFontDatabase>
#include "MainWindow.h"
int main( int argc, char **argv )
{
	QApplication app( argc, argv );
	MainWindow mw;

	//set font
	QFontDatabase database;
	int result = database.addApplicationFont("rsc/font/CabinSketch-Regular.ttf"); 

	QFont ft("CabinSketch",12); 
	mw.setFont(ft);

	mw.show();
	return app.exec();
}
