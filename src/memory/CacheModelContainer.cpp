#include "CacheModelContainer.h"

CacheModelContainer::CacheModelContainer(){
    CacheModel* mainMemory = new CacheModel(Cache::BOTH, 32,0,0,MAIN_MEMORY_DELAY);
    mainMemory->id = id++;
    dataModel = mainMemory;
    instructionModel = mainMemory;
    map.insert(mainMemory->id, mainMemory);
}

CacheModelContainer::~CacheModelContainer(){
    //remove all cache in hashmap
    for(int key : map.keys()){
        delete map[key];
    }
}

