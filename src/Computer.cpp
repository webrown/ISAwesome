#include "Computer.h"
#include <QDebug>

Computer::Computer(){
    if(isInitialized == true){
       qDebug() << "There can be only one computer object" << endl;
       exit(-1);
    }
    isInitialized = true;
}
