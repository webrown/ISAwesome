#ifndef CACHEMODELCONTAINER_H
#define CACHEMODELCONTAINER_H
#include "MemoryInterface.h"
#include <QMap>
#include "../computer/Architecture.h"
#include <QDebug>
#include <QComboBox>
class MemoryStructure{
    public:
    MemoryInterface* instructionModel = NULL;
    CacheModel* dataModel = NULL;
    QMap<int, MemoryInterface*> map;
    int id = 0;
    CacheModelContainer();
    ~CacheModelContainer();

    bool addCacheModel(int nextId, MemoryInterface::Type type, int indexBits, int logDataWordCount, int logAssociativity, double delay);
    bool removeModel(int id);


    static void setUpPlz(QComboBox* box, CacheModelContainer * container);
    QStringList getNames();
    CacheModel* findPrev(CacheModel * target, Cache::CacheType type);

};
#endif
