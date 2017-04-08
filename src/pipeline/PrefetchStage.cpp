#include "PrefetchStage.h"

void PrefetchStage::cycleUp(void){
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
void PrefetchStage::cycleDown(void){
    if(currData != NULL){
        return;
    }
    //Fetch new instruciton.
    currData = pool->get();
    currData->info = 0;

    QueryResult * qr =NULL;
    qr = mems->getInstructionAccess()->read(regs->getPC());

    //Get the data into system.
    currData->instruction = qr->result.at(0).asUInt;  
    // delay = qr->time;
    delay = 1;

    delete qr;
    return;
}
