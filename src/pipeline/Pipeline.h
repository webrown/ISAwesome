#ifndef PIPELINE_H
#define PIPELINE_H
#include "../memory/MemoryInterface.h"
#include "../memory/Register.h"
#include "StageData.h"

class Pipeline {
    public:
        Pipeline(MemoryInterface *dataMemory, MemoryInterface *instructionMemory, Register *registers);

        MemoryInterface *dataMemory;
        MemoryInterface *instructionMemory;
        Register *registers;

        void cycle();
        void _writeBack();
        void _memory();
        void _execute();
        void _decode();
        void _instructionFetch();

        StageData *_writeBackStageData;
        StageData *_memoryStageData;
        StageData *_executeStageData;
        StageData *_decodeStageData;
        StageData *_instructionFetchStageData;

        bool _writeBackStageDone;
        bool _memoryStageDone;
        bool _executeStageDone;
        bool _decodeStageDone;
        bool _instructionFetchStageDone;

        double _instructionFetchStageWait;
};
#endif
