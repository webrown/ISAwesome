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
    // Debug stage listing
#if 1
    QString debugStageListing;
    debugStageListing += Pipeline::stageDebug("IF", &prefetchStage);
    debugStageListing += "   ";
    debugStageListing += Pipeline::stageDebug("D", &decodeStage);
    debugStageListing += "   ";
    debugStageListing += Pipeline::stageDebug("EX", &executeStage);
    debugStageListing += "   ";
    debugStageListing += Pipeline::stageDebug("MEM", &memoryStage);
    debugStageListing += "   ";
    debugStageListing += Pipeline::stageDebug("WB", &writeStage);
    qDebug() << "COM: Pipeline: " << debugStageListing;
#endif

    // Actual functionality
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

QString Pipeline::stageDebug(QString label, Stage *stage){
    QString result = label + ": ";
    if(stage->currData != NULL) {
      result += QString::number(stage->currData->instructionAddress);
      if(stage->currData->instructionFunctions != NULL) {
        QVector<char> from = stage->currData->instructionFunctions->registerDependencies(stage->currData);
        QVector<char> to = stage->currData->instructionFunctions->registersToSet(stage->currData);
        result += "( ";
        for(int i = 0; i < from.size(); i++) {
          result += QString::number(from.at(i)) + " ";
        }
        result += ")";
        result += "->";
        result += "( ";
        for(int i = 0; i < to.size(); i++) {
          result += QString::number(to.at(i)) + " ";
        }
        result += ")";
      }
    }
    else {
      result += "---";
    }
    return result;
}
