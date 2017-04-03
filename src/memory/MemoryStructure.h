#ifndef MEMORY_STRUCTURE_H
#define MEMORY_STRUCTURE_H
#include "MemoryInterface.h"
#include "MainMemory.h"
#include "Cache.h"
#include <QComboBox>
#include <QDebug>
#include "../computer/Architecture.h"

class MemoryStructure {
    public:
        QMap<int, MemoryInterface*> map;
        int id = 0;
        bool isDummy;

        MemoryInterface *_dataAccess = NULL;
        MemoryInterface *_instructionAccess = NULL;
        MainMemory *_mainMemory;
        

        MemoryStructure(double mainMemoryDelay, bool isDummy);
        ~MemoryStructure();

        MemoryInterface *getDataAccess();
        MemoryInterface *getInstructionAccess();
        MemoryInterface *getLastAdded();
        bool addCache(int nextId, MemoryInterface::Type type, int indexBits, int logDataWordCount, int logAssociativity, double delay);
        bool removeCache(int id);
        void clear();


        QStringList getNames();
        QList<QPair<QString, int>> getIds();

        MemoryInterface* findPrev(MemoryInterface * target, MemoryInterface::Type type);
        static void setUpPlz(QComboBox* box, MemoryStructure * container);
        static MemoryInterface::Type convert(int i){
            if(i ==0) return MemoryInterface::DATA_ONLY;
            if(i ==1) return MemoryInterface::INSTRUCTION_ONLY;
            if(i ==2) return MemoryInterface::BOTH;

        }

        //Deprecated
        MemoryInterface *_lastAdded = NULL;
        Cache *pushCache(int indexBits, int logDataWordCount, int logAssociativity, double delay); // Place cache on top of lastAdded.
        void init();
        void pushCache(Cache *newCache); // Place cache on top of lastAdded.
        void goBack(); // Change lastAdded to previous lastAdded.
        void setToInstructionAccess(); // Sets lastAdded to be instruction access point.
        void setToDataAccess();


};
#endif
