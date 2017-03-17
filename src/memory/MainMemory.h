#ifndef MAINMEMORY_H
#define MAINMEMORY_H

#include "MemoryInterface.h"

using namespace std;

//Implement me plz!!
class MainMemory : MemoryInterface{
  public:
    using MemoryInterface::write;
    // Using Young's idea:  Rather than having a single massive vector, memory 
    // is broken into chunks.  A chunk is only ever instantiated if asked for.
    // Assuming spacial locality, this should save a lot of memory!
    const static size_t MEMORY_CHUNK_SIZE = 65536;
    const static size_t MEMORY_CHUNKS = 65536;
    QVector< QVector< Value > > _contents;
    double delay;
    MainMemory(double delay);
    ~MainMemory();
    QueryResult *read(unsigned int address, unsigned int length);
    QueryResult *read(unsigned int address);
    double write(QVector<Value> *value, unsigned int address);
    double write(Value value, unsigned int address);
    QString *save();
    void restore(QString *state);
    void indexPair(unsigned int address, int *firstIndex, int *secondIndex);
};

#endif
