#ifndef MEMORY_STRUCTURE_H
#define MEMORY_STRUCTURE_H
#include "MemoryInterface.h"
#include "MainMemory.h"
#include "Cache.h"
class MemoryStructure {
    public:
        MemoryStructure(double mainMemoryDelay);
        ~MemoryStructure();
        MemoryInterface *_lastAdded;
        MemoryInterface *_dataAccess;
        MemoryInterface *_instructionAccess;
        MainMemory *_mainMemory;
        
        Cache *pushCache(int indexBits, int logDataWordCount, int logAssociativity, double delay); // Place cache on top of lastAdded.
        void pushCache(Cache *newCache); // Place cache on top of lastAdded.
        void goBack(); // Change lastAdded to previous lastAdded.
        void setToInstructionAccess(); // Sets lastAdded to be instruction access point.
        void setToDataAccess();
        MemoryInterface *getDataAccess();
        MemoryInterface *getInstructionAccess();
        MemoryInterface *getLastAdded();
};
#endif
