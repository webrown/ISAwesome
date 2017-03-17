#include "MainMemory.h"
#include "../Architecture.h"
#include <QDebug>

MainMemory::MainMemory(){
    qDebug() << "MainMemory generated" << endl;
}

MainMemory::~MainMemory(){
    qDebug() << "MainMemory destroyed" << endl;
}

QueryResult* MainMemory::read(unsigned int address, unsigned int length){
    if(length != VECTOR_SIZE && length != 1){
        qDebug() << "Invalid Access: length has to be 1 or " << VECTOR_SIZE << endl;
        exit(-1);
    }
    qDebug() << address << length << endl;
    return NULL;
}

QueryResult* MainMemory::read(unsigned int address){
    return read(address, 1);
}

double MainMemory::write(QVector<int> *value, unsigned int address){
    qDebug() << value << address << endl;
    return 0;
}

double MainMemory::write(int input, unsigned int address){
  QVector<int> *tinyQVector = new QVector<int>(1, input);
  double result = write(tinyQVector, address);
  delete tinyQVector;
  return result;
}


QString *MainMemory::save(){
  return new QString("");
}

void MainMemory::restore(QString *state){
  qDebug() << state << endl;
}

