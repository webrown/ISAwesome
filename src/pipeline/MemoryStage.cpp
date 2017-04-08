#include "MemoryStage.h"

void MemoryStage::cycleUp(void){
    //Check delay
    delay--;
    if(delay > 0){
        return;
    }
    else{
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
    if(currData == NULL){
        return;
    }
    if(currData->isSquashed() == true){
        delay = 0;
        return;
    }
    //Process memory instruction here.
}


