#include "WriteStage.h"
#include "Instruction.h"

void WriteStage::cycleUp(void){
    //Check delay
    delay--;
    if(delay > 0){
        return;
    }
    else{
        if(currData != NULL){
            pool->kill(currData);
            currData = NULL;
        }
    }
}

void WriteStage::cycleDown(void){
    // TODO add this stuff to proper places
    if(currData == NULL || currData->instructionFunctions == NULL){
        return;
    }
    if(currData->isSquashed() == true){
        return;
    }
    //uint destReg = currData->destReg;
    //if(destReg < 24){
    //    qDebug() << destReg << currData->dest.asUInt;
    //    regs->write(currData->dest.asUInt, destReg);
    //}
    //else{
    //    regs->write(currData->destVec, destReg);
    //}
    // Do writeback
    currData->instructionFunctions->writeBack(currData, regs);
    delay = 1;
}
