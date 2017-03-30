#ifndef CACHE_H
#define CACHE_H

#include "QueryResult.h"
#include "MemoryInterface.h"
#include <QString>
#include <vector>
#include "Value.h"

using namespace std;
class CacheView;

class Cache : public MemoryInterface{

  public:
    using MemoryInterface::write;

    QVector< QVector<int> * > *tags;
    QVector< QVector< QVector<Value> * > * > *contents;
    QVector< QVector<int> * > *LRU;
    QVector< QVector<int> * > *dirty;
    QVector< QVector<int> * > *valid;


    Cache(int indexBits, int logDataWordCount, int logAssociativity, double delay, Cache *nextMemory);
    virtual ~Cache();
    void init();

    QueryResult *read(unsigned int address, unsigned int length);
    QueryResult *read(unsigned int address);
    double write(QVector<Value> *value, unsigned int address);
    double write(Value value, unsigned int address);

    QByteArray save();
    void restore(QByteArray state);

    //private
    QVector<int> *splitAddress(unsigned int address);
    int addressWay(unsigned int address);
    double fetch(unsigned int address);
    unsigned int firstInLine(unsigned int address);
    void updateLRU(unsigned int address);
    unsigned int getLRUWay(unsigned int index);
    unsigned int buildAddress(unsigned int tag, unsigned int index, unsigned int offset);
    QString toTable();
    size_t maxLength(unsigned int startAddress);
};

#endif
