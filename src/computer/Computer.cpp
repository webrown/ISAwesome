#include "Computer.h"
#include <QDebug>

Computer::Computer(){
    qDebug() << "Creating computer";
    mem = new MainMemory(MAIN_MEMORY_DELAY);
    regs = new Register();
}
Computer::~Computer(){
    qDebug() << "Removing Computer";
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

void Computer::addBreakPoint(BreakPoint bp){
    breakPointQueue.push(bp);
}

bool Computer::removeBreakPoint(BreakPoint bp){
    QQueue<BreakPoint> queue;
    bool found = false;
    while(!breakPointQueue.empty()){
        BreakPoint _bp = breakPointQueue.top();
        if(_bp == bp){
            found = true;
            break; 
        }
        queue.enqueue(bp);
        breakPointQueue.pop();
    }
    while(!queue.empty()){
        breakPointQueue.push(queue.dequeue());
    }
    return true;
}
