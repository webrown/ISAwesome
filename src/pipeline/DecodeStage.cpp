#include "DecodeStage.h"
#include "BranchInstruction.h"
#define L_BIT  toB("1000000000000000000000")
#define L2_BIT toB("0000000100000000000000")



void DecodeStage::cycleUp(void){
    //Check delay
    delay--;
    if(delay > 0){
        return;
    }
    else{
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
    currData->condFlag = vvv & (15u << 28);
    currData->opcode = Opcode::opcodes[(vvv>>22 )& (63u)];

    if(currData->instructionFunctions == NULL) {
      // What instruction are we looking at?
      switch(currData->opcode){
          case Opcode::B: 
              currData->instructionFunctions = new BranchInstruction();
              //currData->dest = {vvv & ((1<<23)-1)};
              //currData->destReg= 23;
              //currData->regInUse = 0;
              break;
          case Opcode::BL:
              if(isDependent(vvv & 31)){
                  dependencyFlag= true;
                  return;
              }
              currData->dest = regs->read(vvv & 31);
              currData->destReg= 23;
              currData->regInUse = 1 << (vvv & 31);
              break;
          case Opcode::SEQ:
              if(isDependent(vvv & 31)){
                  dependencyFlag = true;
                  return;
              }
              //set type bit to vector;
              currData->info |= StageData::VECTOR;
              currData->info |= StageData::FLOAT;

              currData->destVec = regs->readVector(vvv & 31);
              currData->destReg= vvv & 31;
              currData->regInUse = 1 << (vvv & 31);
              break;
          case Opcode::WVE:
          case Opcode::RVE:
              {
                  if(isDependent((vvv > 15) & 31) || isDependent(vvv & 31)){
                      dependencyFlag= true;
                      return;
                  }
                  currData->info |= StageData::VECTOR;
                  //TODO chekc float or not

                  //get auxillary
                  if(vvv & L2_BIT == L2_BIT){
                      currData->src = {(vvv & ((((1 << 5)-1))<<8))>>8};
                  }
                  else{
                      int _ = ((vvv & ((((1 << 5)-1))<<8))>>8);
                      if(isDependent( _)){
                          dependencyFlag = true;
                          return;
                      }
                      uint aux = regs->read({_}).asUInt;
                      currData->aux = regs->read(aux);
                      currData->regInUse |= 1 << aux;
                  }

                  //get source 
                  uint src = regs->read((vvv >>15) & 31).asUInt;
                  if(src < 24){
                      currData->src = regs->read(src);
                  }
                  else{
                      currData->srcVec = regs->readVector(src);
                  }
                  currData->regInUse = 1 << src;


                  //get destination
                  uint dest = regs->read(vvv & 31).asUInt;
                  if(dest < 24){
                      currData->dest = regs->read(dest);
                  }
                  else{
                      currData->destVec = regs->readVector(dest);
                  }
                  currData->destReg = dest;
                  currData->regInUse |= 1 << dest;
                  break;
              }

          case Opcode::CMP:
          case Opcode::LOD:
          case Opcode::STO:
          case Opcode::MVD:
          case Opcode::MVU:
          case Opcode::ARR:
          case Opcode::MOE:
          case Opcode::SOE:
          case Opcode::ADD:
          case Opcode::ADDS:
          case Opcode::ADC:
          case Opcode::ADCS:
          case Opcode::SUB:
          case Opcode::SUBS:
          case Opcode::SBC:
          case Opcode::SBCS:
          case Opcode::MUL:
          case Opcode::MULS:
          case Opcode::LMUL:
          case Opcode::LMULS:
          case Opcode::DIV:
          case Opcode::DIVS:
          case Opcode::LDIV:
          case Opcode::LDIVS:
          case Opcode::MOD:
          case Opcode::MODS:
          case Opcode::LSR:
          case Opcode::LSRS:
          case Opcode::LSL:
          case Opcode::LSLS:
          case Opcode::ASL:
          case Opcode::ASLS:
          case Opcode::AND:
          case Opcode::ANDS:
          case Opcode::NAND:
          case Opcode::NANDS:
          case Opcode::OR:
          case Opcode::ORS:
          case Opcode::NOR:
          case Opcode::NORS:
          case Opcode::XOR:
          case Opcode::XORS:
          case Opcode::NOT:
          case Opcode::NOTS:
              {
                  //check Float or not
                  if(isDependent(vvv&31)){
                      dependencyFlag= true;
                      return;
                  }
                  if(vvv & L_BIT == L_BIT){
                      currData->src = {(vvv & ((((1 << 16)-1))<<5))>>5};
                      currData->regInUse = 0;
                  }
                  else{
                      int _ = ((vvv & ((((1 << 5)-1))<<5))>>5);
                      if(isDependent(_)){
                          dependencyFlag= true;
                          return;
                      }
                      uint src = regs->read({_}).asUInt;
                      if(src < 24){
                          currData->src = regs->read(src);
                      }
                      else{
                          currData->info |= StageData::VECTOR;
                          currData->srcVec = regs->readVector(src);
                      }
                      currData->regInUse = 1 << src;
                  }
                  uint dest = regs->read(vvv & 31).asUInt;
                  if(dest < 24){
                      currData->dest = regs->read(dest);
                  }
                  else{
                      currData->info |= StageData::VECTOR;
                      currData->destVec = regs->readVector(dest);
                  }
                  currData->destReg = dest;
                  currData->regInUse |= 1 << dest;
                  break;
              }
          case Opcode::NOP:
          default:
              //Do nothing
              break;
      }
    }
    
    dependencyFlag = false;
    if(currData == NULL || currData->instructionFunctions == NULL) {
      // Something's gone wrong.  Don't die, just notify.
      qDebug() << "COM:  DecodeStage: Not sure what to do with opcode" << currData->opcode;
      return;
    }
    if(isDependent(currData)) {
        // Hey!  We can't decode this instruction yet!  Its dependencies are not resolved!
        dependencyFlag= true;
        return;
    }

    // Decode the instruction.
    currData->instructionFunctions->decode(currData, regs);

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
    return sd && sd->instructionFunctions && isDependent(sd->instructionFunctions->registerDependencies(sd));
}


