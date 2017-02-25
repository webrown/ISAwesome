#ifndef CACHE_H
#define CACHE_H

#include "CacheResult.h"

class Cache{
  public:
    int tag_bits;
    int index_bits;
    int log_data_word_count;
    float delay;
    Cache *prev_cache;
    Cache *next_cache;
    Cache(int tag_bits, int index_bits, int log_data_word_count, float delay, Cache *prev_cache, Cache *next_cache);
    CacheResult *read(unsigned int address, unsigned int length);
    float write(vector<int> *value, unsigned int address);
    string *save();
    void restore(string *xml);
};

#endif
