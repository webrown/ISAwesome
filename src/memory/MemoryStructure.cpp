#include "MemoryStructure.h"

MemoryStructure::MemoryStructure(double mainMemoryDelay) {
    _mainMemory = new MainMemory(mainMemoryDelay);
    _lastAdded = _mainMemory;
    _dataAccess = _mainMemory;
    _instructionAccess = _mainMemory;
}

MemoryStructure::~MemoryStructure() {
    delete _mainMemory;
    //TODO Erase cache
}

void MemoryStructure::init(){
    _mainMemory->init();
    //TODO init caches
}



void MemoryStructure::pushCache(Cache *newCache) {
    newCache->nextMemory = _lastAdded;
    _lastAdded = newCache;
}

Cache *MemoryStructure::pushCache(int indexBits, int logDataWordCount, int logAssociativity, double delay) {
    Cache *result = new Cache(indexBits, logDataWordCount, logAssociativity, delay, NULL);
    pushCache(result);
    return result;
}

void MemoryStructure::goBack() {
    if(_lastAdded != _mainMemory) {
        _lastAdded = static_cast<Cache*>(_lastAdded)->nextMemory;
    }
}

void MemoryStructure::setToInstructionAccess() {
    _instructionAccess = _lastAdded;
}

void MemoryStructure::setToDataAccess() {
    _dataAccess = _lastAdded;
}

MemoryInterface *MemoryStructure::getDataAccess() {
    return _dataAccess;
}

MemoryInterface *MemoryStructure::getInstructionAccess() {
    return _instructionAccess;
}

MemoryInterface *MemoryStructure::getLastAdded() {
    return _lastAdded;
}

