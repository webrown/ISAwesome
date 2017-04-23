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
            next->computing = false; // Produce your result before you start counting.
            computing = false; // You're done computing for now.
            currData = NULL;
        }
    }
}

void MemoryStage::cycleDown(void){
    if(currData == NULL || currData->instructionFunctions == NULL){
        return;
    }

    if(computing){
        // If you're already computing, everything is in place and you don't need to wait for prereqs and such.
        return;
    }

    if(currData->isSquashed() == true){
        delay = 0;
        return;
    }
    //Process memory instruction here.
    currData->instructionFunctions->memory(currData, mems, &delay);
    computing = true;
}


