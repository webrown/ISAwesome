#ifndef CACHE_H
#define CACHE_H

#include "CacheResult.h"
#include <string>
#include <vector>

using namespace std;

class Cache{
  public:
    int tagBits;
    int indexBits;
    int logDataWordCount;
    int logAssociativity;
    float delay;
    Cache *prevCache;
    Cache *nextCache;
    vector< vector<int> * > *tags;
    vector< vector< vector<int> * > * > *contents;
    vector< vector<int> * > *LRU;
    vector< vector<int> * > *dirty;
    Cache(int tagBits, int indexBits, int logDataWordCount, int logAssociativity, float delay, Cache *prevCache, Cache *nextCache);
    CacheResult *read(unsigned int address, unsigned int length);
    CacheResult *read(unsigned int address);
    float write(vector<int> *value, unsigned int address);
    float write(int value, unsigned int address);
    string *save();
    void restore(string *xml);
    vector<int> *splitAddress(unsigned int address);
};

#endif
