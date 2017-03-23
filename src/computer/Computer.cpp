#include "Computer.h"
#include <QDebug>

Computer::Computer(){
    qDebug() << "Creating computer";
    regs = new Register();
    mems = new MemoryStructure(MAIN_MEMORY_DELAY);
}
Computer::~Computer(){
    qDebug() << "Removing Computer";
    delete regs;
    delete mems;
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
    mems->_mainMemory->write(vec, 0);
}

Status 

void Computer::addBreakPoint(uint address, BreakPoint bp){
    breakMap[address] = bp;
}

void Computer::removeBreakPoint(uint address){
    breakMap.remove(address);
}
