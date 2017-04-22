#include "PrefetchStage.h"
#include "Instruction.h"
#include "../Utility.h"

#include "DecodeStage.h"
#include "BitwiseGroup.h"
#include "ShiftGroup.h"
#include "ConversionGroup.h"
#include "CpyInstruction.h"
#include "BranchAndLinkInstruction.h"
#include "BranchInstruction.h"
#include "CompareInstruction.h"
#include "LoadInstruction.h"
#include "LongAddInstruction.h"
#include "ReadVectorElementInstruction.h"
#include "SequenceInstruction.h"
#include "ShortArithGroup.h"
#include "StoreInstruction.h"
#include "WriteVectorElementInstruction.h"
#include "../memory/Flag.h"
#include "../Utility.h"

void PrefetchStage::cycleUp(void){
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
void PrefetchStage::cycleDown(void){
    if(currData != NULL){
        return;
    }
    if(makeSequential){
        // Do not fetch unles the pipeline is empty.
        for(Stage * curr = next ; curr != NULL ; curr = curr->next){
            if(curr->currData != NULL){
                return;
            }
        }
    }
    else {
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

    // Figure out what instruction this is.
    uint vvv = currData->instruction;
    currData->opcode = Opcode::opcodes[(vvv>>22 )& (63u)];

    if(currData->instructionFunctions == NULL) {
      // What instruction are we looking at?
      switch(currData->opcode){
          case Opcode::B: 
              currData->instructionFunctions = new BranchInstruction();
              break;

          case Opcode::BL:
              currData->instructionFunctions = new BranchAndLinkInstruction();
              break;

          case Opcode::SEQ:
              currData->instructionFunctions = new SequenceInstruction();
              break;

          case Opcode::WVE:
              currData->instructionFunctions = new WriteVectorElementInstruction();
              break;

          case Opcode::RVE:
              currData->instructionFunctions = new ReadVectorElementInstruction();
              break;

          case Opcode::CMP:
              currData->instructionFunctions = new CompareInstruction();
              break;

          case Opcode::CPY:
              currData->instructionFunctions = new CpyInstruction();
              break;

          case Opcode::LOD:
              currData->instructionFunctions = new LoadInstruction();
              break;

          case Opcode::STO:
              currData->instructionFunctions = new StoreInstruction();
              break;

          case Opcode::MVD:
              // TODO
              break;

          case Opcode::MVU:
              // TODO
              break;

          case Opcode::ARR:
              // TODO
              break;


          case Opcode::SOE:
          case Opcode::ADD:
          case Opcode::ADDS:
              currData->instructionFunctions = new AddInstruction();
              break;
          
          case Opcode::ADC:
          case Opcode::ADCS:
              currData->instructionFunctions = new LongAddInstruction();
              break;

          case Opcode::SUB:
          case Opcode::SUBS:
              currData->instructionFunctions = new SubInstruction();
              break;

          case Opcode::SBC:
          case Opcode::SBCS:
              //TODO fill me in
              break;

          case Opcode::MOE:
          case Opcode::MUL:
          case Opcode::MULS:
              currData->instructionFunctions = new MulInstruction();
              break;

          case Opcode::LMUL:
          case Opcode::LMULS:
              //TODO
              break;

          case Opcode::DIV:
          case Opcode::DIVS:
              currData->instructionFunctions = new DivInstruction();
              break;

          case Opcode::LDIV:
          case Opcode::LDIVS:
              //TODO
              break;

          case Opcode::MOD:
          case Opcode::MODS:
              currData->instructionFunctions = new ModInstruction();
              break;

          case Opcode::LSR:
          case Opcode::LSRS:
              currData->instructionFunctions = new LsrInstruction();
              break;

          case Opcode::LSL:
          case Opcode::LSLS:
              currData->instructionFunctions = new LslInstruction();
              break;

          case Opcode::ASL:
          case Opcode::ASLS:
              currData->instructionFunctions = new AslInstruction();
              break;

          case Opcode::ASR:
          case Opcode::ASRS:
              currData->instructionFunctions = new AsrInstruction();
              break;

          case Opcode::AND:
          case Opcode::ANDS:
              currData->instructionFunctions = new AndInstruction();
              break;

          case Opcode::NAND:
          case Opcode::NANDS:
              currData->instructionFunctions = new NandInstruction();
              break;

          case Opcode::OR:
          case Opcode::ORS:
              currData->instructionFunctions = new OrInstruction();
              break;

          case Opcode::NOR:
          case Opcode::NORS:
              currData->instructionFunctions = new NorInstruction();
              break;

          case Opcode::XOR:
          case Opcode::XORS:
              currData->instructionFunctions = new XorInstruction();
              break;

          case Opcode::NOT:
          case Opcode::NOTS:
              currData->instructionFunctions = new NotInstruction();
              break;

          case Opcode::TOF:
              currData->instructionFunctions = new TofInstruction();
              break;

          case Opcode::TOI:
              currData->instructionFunctions = new ToiInstruction();
              break;
              
          case Opcode::NOP:
          default:
              //Do nothing
              break;
      }
    }

    //// If this instruction or the one in Decode right now wants PC, we can't change it yet.
    //for(Stage * curr = this ; curr != this->next->next ; curr = curr->next){
    //    if(curr->currData == NULL || curr->currData->instructionFunctions == NULL){
    //        continue;
    //    }
    //    QVector<char> wants = curr->currData->instructionFunctions->registerDependencies(curr->currData);
    //    for(int i = 0; i < wants.size(); i++) {
    //        if(wants.at(i) == Register::PC) {
    //            // Hey!  This stage wants the PC stable!
    //            return;
    //        }
    //    }
    //}

    // Gear up for loading the next instruction
    regs->write(regs->getPC()+1, Register::PC);
    return;
}

