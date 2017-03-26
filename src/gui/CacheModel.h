#ifndef CACHEMODEL_H
#define CACHEMODEL_H
#include "../memory/Cache.h"

class CacheModel{
    public:
    Cache::CacheType type;
    int level;
    int indexBits;
    int logDataWordCount;
    int logAssociativity;
    double delay;
};
#endif
