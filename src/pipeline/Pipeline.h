#ifndef PIPELINE_H
#define PIPELINE_H
#include "../memory/MemoryInterface.h"
#include "../memory/Register.h"
#include "../memory/MemoryStructure.h"
#include "StageData.h"
#include "../banana/Banana.h"
#include "PrefetchStage.h"
#include "DecodeStage.h"
#include "MemoryStage.h"
#include "ExecuteStage.h"
#include "WriteStage.h"


class Pipeline : public Banana{
    public:
        Register *registers;
        MemoryStructure *memory;
        StageDataPool pool;

        Pipeline(Register * regs, MemoryStructure *mem);
        ~Pipeline();

        void init();
        Status run(void);
        void stop(void);

        PrefetchStage prefetchStage;
        DecodeStage decodeStage;
        ExecuteStage executeStage;
        MemoryStage memoryStage;
        WriteStage writeStage;
        // bool _writeBackStageDone;
        // bool _memoryStageDone;
        // bool _executeStageDone;
        // bool _decodeStageDone;
        // bool _instructionFetchStageDone;
        //
        /* double _instructionFetchStageWait; */
};
#endif
