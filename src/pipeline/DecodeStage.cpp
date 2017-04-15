#include "DecodeStage.h"
#include "ShortArithGroup.h"
#include "BitwiseGroup.h"
#include "ShiftGroup.h"
#include "ConversionGroup.h"
#include "CpyInstruction.h"
#include "BranchInstruction.h"
#include "CompareInstruction.h"
#include "LongAddInstruction.h"
#include "WriteVectorElementInstruction.h"
#include "../memory/Flag.h"
#include "../Utility.h"
#define L_BIT  toB("1000000000000000000000")
#define L2_BIT toB("0000000100000000000000")



void DecodeStage::cycleUp(void){
    //Check delay
    delay--;
    if(delay > 0){
        return;
    } else{
        if(next->currData != NULL || dependencyFlag){
            //Structural hazard
            return;
        }
        else{
            next->currData = currData;
            currData = NULL;
        }
    }
}
using namespace Opcode;
void DecodeStage::cycleDown(void){
    if(currData == NULL){
        return;
    }

    uint vvv = currData->instruction;

    qDebug() << "COM: DecodeStage: Sees instruction " << intToBinary(currData->instruction) << ", PC of" << currData->instructionAddress;
    
    unsigned int flagCode = (vvv >> 28) & 15u;
    if(flagCode ==  0) currData->condFlag = Flag::EQ;
    if(flagCode ==  1) currData->condFlag = Flag::NE;
    if(flagCode ==  2) currData->condFlag = Flag::CS;
    if(flagCode ==  3) currData->condFlag = Flag::CC;
    if(flagCode ==  4) currData->condFlag = Flag::MI;
    if(flagCode ==  5) currData->condFlag = Flag::PL;
    if(flagCode ==  6) currData->condFlag = Flag::VS;
    if(flagCode ==  7) currData->condFlag = Flag::VC;
    if(flagCode ==  8) currData->condFlag = Flag::DZ;
    if(flagCode ==  9) currData->condFlag = Flag::NZ;
    if(flagCode == 10) currData->condFlag = Flag::LE;
    if(flagCode == 11) currData->condFlag = Flag::GE;
    if(flagCode == 12) currData->condFlag = Flag::LT;
    if(flagCode == 13) currData->condFlag = Flag::GT;
    if(flagCode == 14) currData->condFlag = Flag::AL;
    if(flagCode == 15) currData->condFlag = Flag::UN;

    currData->opcode = Opcode::opcodes[(vvv>>22 )& (63u)];

    if(currData->instructionFunctions == NULL) {
      // What instruction are we looking at?
      switch(currData->opcode){
          case Opcode::B: 
              currData->instructionFunctions = new BranchInstruction();
              break;
          case Opcode::BL:
              break;
          case Opcode::SEQ:
              break;
          case Opcode::WVE:
              currData->instructionFunctions = new WriteVectorElementInstruction();
              break;
          case Opcode::RVE:
              //TODO insert something here
          case Opcode::CMP:
              currData->instructionFunctions = new CompareInstruction();
              break;
          case Opcode::CPY:
              currData->instructionFunctions = new CpyInstruction();
              break;
          case Opcode::LOD:
          case Opcode::STO:
          case Opcode::MVD:
          case Opcode::MVU:
          case Opcode::ARR:
          case Opcode::MOE:
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
          case Opcode::MUL:
          case Opcode::MULS:
              currData->instructionFunctions = new MulInstruction();
              break;
          case Opcode::LMUL:
          case Opcode::LMULS:
              //TODO 
          case Opcode::DIV:
          case Opcode::DIVS:
              currData->instructionFunctions = new DivInstruction();
              break;

          case Opcode::LDIV:
          case Opcode::LDIVS:
              //TODO 
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
              
          case Opcode::NOP:
          default:
              //Do nothing
              break;
      }
    }
    
    if(currData == NULL || currData->instructionFunctions == NULL) {
      // Something's gone wrong.  Don't die, just notify.
      qDebug() << "COM:  DecodeStage: Not sure what to do with opcode" << currData->opcode;
      return;
    }

    // Try to decode, just for the heck of it.  Might get dumped later.
    currData->instructionFunctions->decode(currData, regs);

    dependencyFlag = false;
    if(isDependent(currData)) {
        // Hey!  We can't decode this instruction yet!  Its dependencies are not resolved!
        dependencyFlag= true;
        return;
    }

    // OK!  Flags are settled!  We checked if anyone was messing with -1 in dependencies!
    currData->flagValue  = Flag::has(regs->readFlag(), currData->condFlag);
    currData->flagValues = Flag::has(regs->readFlags(), currData->condFlag);

    // If this instruction obeys the scalar flag or is malformed, we might be able to remove it now.
    if(currData->instructionFunctions->decodeDump(currData, regs) || currData->broken) {
        delete currData;
        currData = NULL;
    }
#if 1
qDebug() << "COM: DecodeStage: Newly decoded instruction:";
if(currData != NULL) {
  qDebug() << "COM: DecodeStage: src:"  << currData->src.i;
  qDebug() << "COM: DecodeStage: dest:" << currData->dest.i;
}
else {
  qDebug() << "COM: DecodeStage: NULLED out";
}
#endif
    delay = 1;
}

bool DecodeStage::isDependent(char regNum) const{
    for(Stage * curr = next ; curr != NULL ; curr = curr->next){
        if(curr->currData == NULL || curr->currData->instructionFunctions == NULL){
            continue;
        }
        QVector<char> willSet = curr->currData->instructionFunctions->registersToSet(curr->currData);
        for(int i = 0; i < willSet.size(); i++) {
            if(willSet.at(i) == regNum) {
                // Hey!  This stage is planning to modify this register!
                return true;
            }
        }
    }
    return false;
}

bool DecodeStage::isDependent(QVector<char> regNums) const{
    for(int i = 0; i < regNums.size(); i++) {
        // NOTE:  Got a SEG around here for a while because one of the functions was missing a return value for registerDependencies
        if(isDependent(regNums.at(i))){
            // Hey!  Some stage is planning to modify this register!
            return true;
        }
    }
    return false;
}

bool DecodeStage::isDependent(StageData *sd) const{
    if(sd == NULL || sd->instructionFunctions == NULL) return false;
    QVector<char> dependencies = sd->instructionFunctions->registerDependencies(sd);
    dependencies.push_back(-1); // -1 = condition flag.  EVERYONE depends on condition flags!
#if 0
qDebug() << "DEPENDENCIES:";
for(int i = 0; i < dependencies.size(); i++) qDebug() << QString::number(dependencies.at(i));
#endif
    return isDependent(dependencies);
}


