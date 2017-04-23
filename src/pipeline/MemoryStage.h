#ifndef MEMORYSTAGE_H
#define MEMORYSTAGE_H
#include "Stage.h"
#include "../memory/MemoryStructure.h"
class MemoryStage :public Stage{
    public: 
        MemoryStructure * mems;
        bool cycleUp(void);
        void cycleDown(void);
};
#endif
