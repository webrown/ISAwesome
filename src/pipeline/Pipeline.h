#include "StageData.h"

class Pipeline {
    public:
        Pipeline(MemoryInterface *dataMemory, MemoryInterface *instructionMemory, Registers *registers) {

        MemoryInterface *dataMemory;
        MemoryInterface *instructionMemory;
        Registers *registers;

        void cycle();
        void _writeBack();
        void _memory();
        void _execute();
        void _decode();
        void _instructionFetch();

        StageData *_writeBackData;
        StageData *_memoryData;
        StageData *_executeData;
        StageData *_decodeData;
        StageData *_instructionFetchData;

        bool _writeBackDone;
        bool _memoryDone;
        bool _executeDone;
        bool _decodeDone;
        bool _instructionFetchDone;

        double _instructionFetchWait;
}
