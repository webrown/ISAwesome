#ifndef EXECUTESTAGE_H
#define EXECUTESTAGE_H
#include "Stage.h"
#include "DecodeStage.h"
#include "MemoryStage.h"

class ExecuteStage : public Stage{
    public: 
        bool cycleUp(void);
        void cycleDown(void);
        
};
#endif
