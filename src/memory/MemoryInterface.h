#ifndef MEMORYINTERFACE_H
#define MEMORYINTERFACE_H

#include <QString>
#include <QVector>
#include "QueryResult.h"

class MemoryInterface{
  public:
    virtual QueryResult *read(unsigned int address, unsigned int length)=0;
    virtual QueryResult *read(unsigned int address)=0;
    virtual double write(QVector<int> *value, unsigned int address)=0;
    virtual double write(int value, unsigned int address)=0;
    virtual QString *save()=0;
    virtual void restore(QString *state)=0;
};

#endif
