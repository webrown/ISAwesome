#ifndef MAINMEMORY_H
#define MAINMEMORY_H

#include "MemoryInterface.h"

using namespace std;

//Implement me plz!!
class MainMemory : MemoryInterface{
  public:
    MainMemory();
    ~MainMemory();
    QueryResult *read(unsigned int address, unsigned int length);
    QueryResult *read(unsigned int address);
    double write(QVector<int> *value, unsigned int address);
    double write(int value, unsigned int address);
    QString *save();
    void restore(QString *state);
};

#endif
