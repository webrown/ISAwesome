#include "Pipeline.h"

Pipeline::Pipeline(MemoryInterface *dataMemory, MemoryInterface *instructionMemory, Registers *registers) {
}

void Pipeline::cycle() {
    _writeBack();
    _memory();
    _execute();
    _decode();
    _instructionFetch();
}

void Pipeline::_writeBack() {
    if(!_writeBackDone) {
        // Write to register file where applicable.
    }
    if(_writeBackDone) {
        // You are done with this instruction.
        _writeBackStageData = NULL;
    }
}

void Pipeline::_memory() {
    if(!_memoryDone) {
        // Where applicable, dump values to memory.
        // OR maybe load values from memory?
    }
    if(_memoryDone) {
        // Try to push this instruction along.
        if(!_writeBackStageData) {
            _writeBackStageData = _memoryStageData;
            _memoryStageData = NULL;
            _writeBackStageDone = false;
        }
    }
}

void Pipeline::_execute() {
    if(!_executeDone) {
        // Do the requested operation
    }
    if(_executeDone) {
        // Try to push this instruction along.
        if(!_memoryStageData) {
            _memoryStageData = _executeStageData;
            _executeStageData = NULL;
            _memoryStageDone = false;
        }
    }
}

void Pipeline::_decode() {
    if(!_decodeDone) {
        // Check that register values and condition values are settled.
        // TODO: there's no speculation for now.
        // Grab register values
        // Grab condition values
        // Determine conditional results; will this fire/for which vector indexes?
        // If this instruction will not fire at all, it can be safely removed.
    }
    if(_decodeDone) {
        // Try to push this instruction along.
        if(!_executeStageData) {
            _executeStageData = _decodeStageData;
            _decodeStageData = NULL;
            _executeStageDone = false;
        }
    }
}

void Pipeline::_instructionFetch() {
    if(!_instructionFetchDone) {
        if(!_instructionFetchData) {
            // Hey, which instruction do you want?  PC will know!
            int nextLine = registers->pc.i;
            // Fetch from instruction memory. (might take some cycles)
            QueryResult *qr = instructionMemory->read(nextLine);
            _instructionFetchWait = qr->time;
            _instructionFetchData = valueToStageData(qr->result->at(0));
            delete qr;
        }
        // Wait for instruction to fetch...
        _instructionFetchWait --;
        if(_instructionFetchWait <= 0) {
            _instructionFetchDone = true;
        }
    }
    if(_instructionFetchDone) {
        // Try to push this instruction along.
        if(!_decodeStageData) {
            _decodeStageData = _instructionFetchStageData;
            _instructionFetchStageData = NULL;
            _decodeStageDone = false;
        }
    }
}

