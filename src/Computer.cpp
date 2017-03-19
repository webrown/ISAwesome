#include "Computer.h"
#include <QDebug>

Computer::Computer(){
    mem = new MainMemory(MAIN_MEMORY_DELAY);
    regs = new Register();
}
Computer::~Computer(){
    qDebug() << "Delete Computer";
    delete mem;
    delete topCache;
    delete regs;
    qDebug() << "Computer is removed!";
}

void Computer::init(QVector<uint>* instructions){
    //demo!
    QVector<Value>* vec = new QVector<Value>();
    for(int i =0 ; i < instructions->size(); i++){
        uint instruction = instructions->at(i); 
        Value v = {instruction};
        vec->append(v);
    }
    mem->write(vec, 0);

}
