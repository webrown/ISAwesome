#include "MemoryStage.h"
#include "Instruction.h"

void MemoryStage::cycleUp(void){
    //Check delay
    delay--;
    if(delay > 0){
        return;
    }
    else{
        this->structureFlag = next->currData != NULL;

        if(next->currData != NULL){
            //Structural hazard
            return;
        }
        else{
            next->currData = currData;
            currData = NULL;
        }
    }
}

void MemoryStage::cycleDown(void){
    if(currData == NULL || currData->instructionFunctions == NULL){
        return;
    }
    if(currData->isSquashed() == true){
        delay = 0;
        return;
    }
    //Process memory instruction here.
    currData->instructionFunctions->memory(currData, mems);
}


