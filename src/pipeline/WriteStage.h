#ifndef WRITESTAGE_H
#define WRITESTAGE_H
#include "Stage.h"
#include "../memory/Register.h"
class WriteStage : public Stage{
    public: 
        StageDataPool * pool;
        Register * regs;
        bool cycleUp(void);
        void cycleDown(void);
};
#endif
