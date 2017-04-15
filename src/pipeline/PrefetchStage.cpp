#include "PrefetchStage.h"
#include "Instruction.h"

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
    //Do not fetch if someone in the pipeline is planning to modify the PC.
    for(Stage * curr = next ; curr != NULL ; curr = curr->next){
        if(curr->currData == NULL || curr->currData->instructionFunctions == NULL){
            continue;
        }
        QVector<char> willSet = curr->currData->instructionFunctions->registersToSet(curr->currData);
        for(int i = 0; i < willSet.size(); i++) {
            if(willSet.at(i) == Register::PC) {
                // Hey!  This stage is planning to modify this register!
                return;
            }
        }
    }
    
    //Fetch new instruciton.
    currData = pool->get();
    currData->info = 0;

    QueryResult * qr =NULL;
    qr = mems->getInstructionAccess()->read(regs->getPC());

    //Get the data into system.
    currData->instruction = qr->result.at(0).asUInt;  
    currData->instructionAddress = regs->getPC();
    delete currData->instructionFunctions;
    currData->instructionFunctions = NULL;
    // delay = qr->time;
    delay = 1;

    delete qr;

    // Gear up for loading the next instruction
    regs->write(regs->getPC()+1, Register::PC);
    return;
}

