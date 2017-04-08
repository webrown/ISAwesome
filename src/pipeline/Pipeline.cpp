#include "Pipeline.h"

Pipeline::Pipeline(Register * regs, MemoryStructure * mem) {
    this->registers =  regs;
    this->memory = mem;
    this->instructionsDone = 0;
    this->cyclesDone = 0;

    //Set the stage link
    prefetchStage.next = (Stage *) &decodeStage;
    prefetchStage.mems = mem;
    prefetchStage.regs =  regs;
    prefetchStage.pool = & pool;

    decodeStage.prev = (Stage *) & prefetchStage;
    decodeStage.next = (Stage *) & executeStage;
    decodeStage.regs = regs;


    executeStage.prev = (Stage *) & decodeStage;
    executeStage.next = (Stage *) & memoryStage;

    memoryStage.prev = (Stage *) & executeStage;
    memoryStage.next = (Stage *) & writeStage;
    memoryStage.mems = mem;

    writeStage.prev = (Stage *) & memoryStage;
    writeStage.regs =regs;
    writeStage.pool = & pool;
}

Pipeline::~Pipeline(){
    //Do nothing
}

void Pipeline::init(){
    prefetchStage.init();
    decodeStage.init();
    executeStage.init();
    memoryStage.init();
    writeStage.init();
}
Status Pipeline::run(){
    writeStage.cycleUp();
    memoryStage.cycleUp();
    executeStage.cycleUp();
    decodeStage.cycleUp();

    prefetchStage.cycleUp();

    writeStage.cycleDown();
    memoryStage.cycleDown();
    executeStage.cycleDown();
    decodeStage.cycleDown();
    prefetchStage.cycleDown();


    //Because..., why not?
    return OKAY;
}
void Pipeline::stop(){
    //Do nothing
}
