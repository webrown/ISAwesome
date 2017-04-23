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
            next->computing = false; // Produce your result before you start counting.
            computing = false; // You're done computing for now.
            currData = NULL;
        }
    }
}

void ExecuteStage::cycleDown(void){
    if(currData == NULL || currData->instructionFunctions == NULL){
        return;
    }
    if(computing){
        // If you're already computed, you don't want to restart your delay timer!
        return;
    }
    if(currData->isSquashed() == true){
        //Nothing to do. let's move on!
        delay = 0;
        return;
    }

    
    
    //Some execute logic here.
    currData->instructionFunctions->execute(currData, &delay);
    computing = true;
}
