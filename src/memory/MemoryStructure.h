#ifndef MEMORY_STRUCTURE_H
#define MEMORY_STRUCTURE_H
#include "MemoryInterface.h"
#include "MainMemory.h"
#include "Cache.h"
class MemoryStructure {
    public:
        MemoryInterface *_lastAdded = NULL;
        MemoryInterface *_dataAccess = NULL;
        MemoryInterface *_instructionAccess = NULL;
        MainMemory *_mainMemory;
        
        MemoryStructure(double mainMemoryDelay);
        ~MemoryStructure();

        Cache *pushCache(int indexBits, int logDataWordCount, int logAssociativity, double delay); // Place cache on top of lastAdded.
        void init();
        void pushCache(Cache *newCache); // Place cache on top of lastAdded.
        void goBack(); // Change lastAdded to previous lastAdded.
        void setToInstructionAccess(); // Sets lastAdded to be instruction access point.
        void setToDataAccess();

        MemoryInterface *getDataAccess();
        MemoryInterface *getInstructionAccess();
        MemoryInterface *getLastAdded();
};
#endif
