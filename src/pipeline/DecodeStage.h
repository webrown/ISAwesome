#ifndef DECODESTAGE_H
#define DECODESTAGE_H
#include "Stage.h" 
#include "PrefetchStage.h"
#include "ExecuteStage.h"
#include "../Utility.h"
#include "../memory/Register.h"
class DecodeStage : public Stage{
    public: 
        bool dependencyFlag; 
        Register * regs;
        void cycleDown(void);
        void cycleUp(void);
        bool isDependent(int regNum);
};
#endif
