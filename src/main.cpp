#include <QApplication>
#include <QSplashScreen>
#include "gui/MainWindow.h"

//https://wiki.qt.io/How_to_create_a_splash_screen_with_an_induced_delay
class I : public QThread
{
public:
    static void sleep(unsigned long secs) { QThread::sleep(secs); }
};

int main( int argc, char **argv )
{
    qDebug() << "Launch Application";
    QApplication app( argc, argv );

    //Why not?
    QPixmap pixmap("pisa.png");
    QSplashScreen splash(pixmap);
    splash.show();


    MainWindow mw;
    mw.setWindowTitle("PISA(Parallel Instruction Set Architecture)");
//    I::sleep(5);

    mw.show();
    splash.finish(&mw);
    return app.exec();
}
