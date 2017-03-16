#include "Computer.h"
#include <QDebug>

Computer::Computer(){
}
Computer::~Computer(){
    qDebug() << "Delete Computer";
    delete mem;
    delete topCache;
    delete regs;
    qDebug() << "Computer is removed!";
}
