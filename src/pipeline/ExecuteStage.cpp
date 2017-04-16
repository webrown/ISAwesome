#include "ExecuteStage.h"
#include "Instruction.h"

void ExecuteStage::cycleUp(void){
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

void ExecuteStage::cycleDown(void){
    if(currData == NULL || currData->instructionFunctions == NULL){
        return;
    }
    if(currData->isSquashed() == true){
        //Nothing to do. let's move on!
        delay = 0;
        return;
    }

    
    
    //Some execute logic here.
    currData->instructionFunctions->execute(currData);

    
    //Some delay logic here
}
