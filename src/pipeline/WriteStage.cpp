#include "WriteStage.h"

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
    if(currData == NULL){
        return;
    }
    if(currData->isSquashed() == true){
        return;
    }
    uint destReg = currData->destReg;
    if(destReg < 24){
        qDebug() << destReg << currData->dest.asUInt;
        regs->write(currData->dest.asUInt, destReg);
    }
    else{
        regs->write(currData->destVec, destReg);
    }
    delay = 1;
}
