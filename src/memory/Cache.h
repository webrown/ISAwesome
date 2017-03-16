#ifndef CACHE_H
#define CACHE_H

#include "QueryResult.h"
#include "MemoryInterface.h"
#include <QString>
#include <vector>

using namespace std;
class CacheView;

enum CacheType{
    DATA, INSTRUCTION, BOTH
};

class Cache : MemoryInterface{
  public:
    CacheType type;
    CacheView* view = NULL;
    int indexBits;
    int logDataWordCount;
    int logAssociativity;
    double delay;
    Cache *prevCache = NULL;
    Cache *nextCache = NULL;
    QVector< QVector<int> * > *tags;
    QVector< QVector< QVector<int> * > * > *contents;
    QVector< QVector<int> * > *LRU;
    QVector< QVector<int> * > *dirty;
    QVector< QVector<int> * > *valid;
    Cache(int indexBits, int logDataWordCount, int logAssociativity, double delay, Cache *nextCache);
    virtual ~Cache();
    QueryResult *read(unsigned int address, unsigned int length);
    QueryResult *read(unsigned int address);
    double write(QVector<int> *value, unsigned int address);
    double write(int value, unsigned int address);
    QString *save();
    void restore(QString *state);
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
