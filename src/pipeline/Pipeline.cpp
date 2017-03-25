#include "Pipeline.h"

Pipeline::Pipeline(MemoryInterface *dataMemory, MemoryInterface *instructionMemory, Register *registers) {
}

void Pipeline::cycle() {
    _writeBack();
    _memory();
    _execute();
    _decode();
    _instructionFetch();
}

void Pipeline::_writeBack() {
    if(!_writeBackStageDone) {
        // Write to register file where applicable.
    }
    if(_writeBackStageDone) {
        // You are done with this instruction.
        _writeBackStageData = NULL;
    }
}

void Pipeline::_memory() {
    if(!_memoryStageDone) {
        // Where applicable, dump values to memory.
        // OR maybe load values from memory?
    }
    if(_memoryStageDone) {
        // Try to push this instruction along.
        if(!_writeBackStageData) {
            _writeBackStageData = _memoryStageData;
            _memoryStageData = NULL;
            _writeBackStageDone = false;
        }
    }
}

void Pipeline::_execute() {
    if(!_executeStageDone) {
        // Do the requested operation
    }
    if(_executeStageDone) {
        // Try to push this instruction along.
        if(!_memoryStageData) {
            _memoryStageData = _executeStageData;
            _executeStageData = NULL;
            _memoryStageDone = false;
        }
    }
}

void Pipeline::_decode() {
    if(!_decodeStageDone) {
        // Check that register values and condition values are settled.
        // TODO: there's no speculation for now.
        // Grab register values
        // Grab condition values
        // Determine conditional results; will this fire/for which vector indexes?
        // If this instruction will not fire at all, it can be safely removed.
    }
    if(_decodeStageDone) {
        // Try to push this instruction along.
        if(!_executeStageData) {
            _executeStageData = _decodeStageData;
            _decodeStageData = NULL;
            _executeStageDone = false;
        }
    }
}

void Pipeline::_instructionFetch() {
    if(!_instructionFetchStageDone) {
        if(!_instructionFetchStageData) {
            // Hey, which instruction do you want?  PC will know!
            int nextLine = registers->getPC();
            // Fetch from instruction memory. (might take some cycles)
            QueryResult *qr = instructionMemory->read(nextLine);
            _instructionFetchStageWait = qr->time;
            _instructionFetchStageData->takeInstructionCode(qr->result.at(0));
            delete qr;
        }
        // Wait for instruction to fetch...
        _instructionFetchStageWait --;
        if(_instructionFetchStageWait <= 0) {
            _instructionFetchStageDone = true;
        }
    }
    if(_instructionFetchStageDone) {
        // Try to push this instruction along.
        if(!_decodeStageData) {
            _decodeStageData = _instructionFetchStageData;
            _instructionFetchStageData = NULL;
            _decodeStageDone = false;
        }
    }
}

