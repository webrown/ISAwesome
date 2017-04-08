#include "ExecuteStage.h"

void ExecuteStage::cycleUp(void){
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

void ExecuteStage::cycleDown(void){
    if(currData == NULL){
        return;
    }
    if(currData->isSquashed() == true){
        //Nothing to do. let's move on!
        delay = 0;
        return;
    }

    
    
    //Some execute logic here.
    switch(currData->opcode){
        case Opcode::B:
            break;
        case Opcode::ADD:
            currData->dest= {currData->dest.asUInt + currData->src.asUInt};
            break;
    }
    //except memory related instruction
    
    //Some delay logic here
}
