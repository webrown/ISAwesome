#ifndef PREFETCHSTAGE_H
#define PREFETCHSTAGE_H
#include <QQueue>
#include "DecodeStage.h"
#include "../memory/MemoryStructure.h"
#include "../memory/Register.h"

/*
 * All stage will be initialized in pipeline.cpp.
 */
class PrefetchStage : public Stage {
    public: 

        MemoryStructure * mems;
        Register * regs;

        StageDataPool * pool;

        bool cycleUp(void);
        void cycleDown(void);

        bool makeSequential = 0;
};
#endif
