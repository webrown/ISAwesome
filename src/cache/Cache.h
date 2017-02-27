#ifndef CACHE_H
#define CACHE_H

#include "CacheResult.h"

class Cache{
  public:
    int tagBits;
    int indexBits;
    int logDataWordCount;
    int logAssociativity;
    float delay;
    Cache *prevCache;
    Cache *nextCache;
    Cache(int tagBits, int indexBits, int logDataWordCount, int logAssociativity, float delay, Cache *prevCache, Cache *nextCache);
    CacheResult *read(unsigned int address, unsigned int length);
    float write(vector<int> *value, unsigned int address);
    float write(int value, unsigned int address);
    string *save();
    void restore(string *xml);
};

#endif
