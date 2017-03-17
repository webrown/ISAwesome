#include <QApplication>
#include "gui/MainWindow.h"

int main( int argc, char **argv )
{
    qDebug() << "Launch Application";
    QApplication app( argc, argv );
    MainWindow mw;
    mw.show();
    return app.exec();
}
