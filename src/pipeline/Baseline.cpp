#include "Baseline.h"
#include "spliceMachineCode.h"
#include "../Utility.h"
#include "PipelineGlobals.h"
Baseline::Baseline(Register *registers, MemoryStructure *memory){
    registers = registers;
    memory = memory;
}

Status Baseline::run(void){
/*     // Complete 1 instruction */
    // QueryResult *qr = NULL;
    // Value value;
    //
    // // Get the next instruction address.
    // qr = registers->read(Register::PC);
    // int pc = qr->result.at(0).i;
    // delete qr;
    // // Get next instruction from memory.
    // qr = memory->getInstructionAccess()->read(pc);
    // unsigned int nextInstruction = qr->result.at(0).asUInt;
    // delete qr;
    // // Move to next instruction address.
    // pc++;
    // // What is instruction type?
    // unsigned int opcode = spliceMachineCode(nextInstruction, 22, 27);
    // Instruction instructionType;
    // if(opcode == toB(QString("000000"))) instructionType     =  B         ;
    // if(opcode == toB(QString("000001"))) instructionType    =  BL         ;
    // if(opcode == toB(QString("000010"))) instructionType   =  CMP         ;
    // if(opcode == toB(QString("000100"))) instructionType   =  CPY         ;
    // if(opcode == toB(QString("000101"))) instructionType   =  LOD         ;
    // if(opcode == toB(QString("000110"))) instructionType   =  STO         ;
    // if(opcode == toB(QString("001000"))) instructionType   =  RVE         ;
    // if(opcode == toB(QString("001001"))) instructionType   =  WVE         ;
    // if(opcode == toB(QString("001010"))) instructionType   =  MVD         ;
    // if(opcode == toB(QString("001011"))) instructionType   =  MVU         ;
    // if(opcode == toB(QString("001100"))) instructionType   =  ARR         ;
    // if(opcode == toB(QString("001101"))) instructionType   =  SEQ         ;
    // if(opcode == toB(QString("001110"))) instructionType   =  SOE         ;
    // if(opcode == toB(QString("001111"))) instructionType   =  MOE         ;
    // if(opcode == toB(QString("010000"))) instructionType   =  ADD         ;
    // if(opcode == toB(QString("010001"))) instructionType  =  ADDS         ;
    // if(opcode == toB(QString("010010"))) instructionType   =  ADC         ;
    // if(opcode == toB(QString("010011"))) instructionType  =  ADCS         ;
    // if(opcode == toB(QString("010100"))) instructionType   =  SUB         ;
    // if(opcode == toB(QString("010101"))) instructionType  =  SUBS         ;
    // if(opcode == toB(QString("010110"))) instructionType   =  SBC         ;
    // if(opcode == toB(QString("010111"))) instructionType  =  SBCS         ;
    // if(opcode == toB(QString("011000"))) instructionType   =  MUL         ;
    // if(opcode == toB(QString("011001"))) instructionType  =  MULS         ;
    // if(opcode == toB(QString("011010"))) instructionType  =  LMUL         ;
    // if(opcode == toB(QString("011011"))) instructionType =  LMULS         ;
    // if(opcode == toB(QString("011100"))) instructionType   =  DIV         ;
    // if(opcode == toB(QString("011101"))) instructionType  =  DIVS         ;
    // if(opcode == toB(QString("011110"))) instructionType  =  LDIV         ;
    // if(opcode == toB(QString("011111"))) instructionType  =  LDIV         ;
    // if(opcode == toB(QString("100000"))) instructionType   =  MOD         ;
    // if(opcode == toB(QString("100001"))) instructionType  =  MODS         ;
    // if(opcode == toB(QString("101000"))) instructionType   =  LSR         ;
    // if(opcode == toB(QString("101001"))) instructionType  =  LSRS         ;
    // if(opcode == toB(QString("101010"))) instructionType   =  LSL         ;
    // if(opcode == toB(QString("101011"))) instructionType  =  LSLS         ;
    // if(opcode == toB(QString("101100"))) instructionType   =  ASL         ;
    // if(opcode == toB(QString("101101"))) instructionType  =  ASLS         ;
    // if(opcode == toB(QString("101110"))) instructionType   =  ASR         ;
    // if(opcode == toB(QString("101111"))) instructionType  =  ASRS         ;
    // if(opcode == toB(QString("110000"))) instructionType   =  AND         ;
    // if(opcode == toB(QString("110001"))) instructionType  =  ANDS         ;
    // if(opcode == toB(QString("110010"))) instructionType  =  NAND         ;
    // if(opcode == toB(QString("110011"))) instructionType =  NANDS         ;
    // if(opcode == toB(QString("110100"))) instructionType    =  OR         ;
    // if(opcode == toB(QString("110101"))) instructionType  =  ORS          ;
    // if(opcode == toB(QString("110110"))) instructionType   =  NOR         ;
    // if(opcode == toB(QString("110111"))) instructionType  =  NORS         ;
    // if(opcode == toB(QString("111000"))) instructionType   =  XOR         ;
    // if(opcode == toB(QString("111001"))) instructionType  =  XORS         ;
    // if(opcode == toB(QString("111010"))) instructionType   =  NOT         ;
    // if(opcode == toB(QString("111011"))) instructionType  =  NOTS         ;
    // if(opcode == toB(QString("111100"))) instructionType   =  TOI         ;
    // if(opcode == toB(QString("111101"))) instructionType   =  TOF         ;
    //
    // // What is the flag?
    // unsigned int flagCode = spliceMachineCode(nextInstruction, 28, 31);
    // Conditional flag;
    // if(flagCode ==  0) flag = EQ;
    // if(flagCode ==  1) flag = NE;
    // if(flagCode ==  2) flag = CS;
    // if(flagCode ==  3) flag = CC;
    // if(flagCode ==  4) flag = MI;
    // if(flagCode ==  5) flag = PL;
    // if(flagCode ==  6) flag = VS;
    // if(flagCode ==  7) flag = VC;
    // if(flagCode ==  8) flag = DZ;
    // if(flagCode ==  9) flag = NZ;
    // if(flagCode == 10) flag = LE;
    // if(flagCode == 11) flag = GE;
    // if(flagCode == 12) flag = LT;
    // if(flagCode == 13) flag = GT;
    // if(flagCode == 14) flag = AL;
    // if(flagCode == 15) flag = UN;
    //
    // // Interpret flag.
    // // TODO base of flag register.
    // QVector<bool> conditionVector(64, true);
    //
    // // Determine if operand 1 is an immediate
    // int useImmediate = !spliceMachineCode(nextInstruction, 21, 21);
    // int useImmediateTernary = !spliceMachineCode(nextInstruction, 14, 14);
    //
    // // Grab unary operand
    // int unaryOperand = spliceMachineCode(nextInstruction, 0, 20);
    //
    // // Grab binary operands
    // int binaryOperand1 = spliceMachineCode(nextInstruction, 5, 20);
    // int binaryOperand2 = spliceMachineCode(nextInstruction, 0, 4);
    //
    // // Grab ternary operands
    // int ternaryOperand1 = spliceMachineCode(nextInstruction, 15, 20);
    // int ternaryOperand2 = spliceMachineCode(nextInstruction, 8, 13);
    // int ternaryOperand3 = spliceMachineCode(nextInstruction, 0, 4);
    //
    // // Do what the instruction tells you to.
    // switch(instructionType) {
    //     case ADD: {
    //         QVector<Value> addThis;
    //         value.i = binaryOperand1;
    //         addThis.push_back(value);
    //         if(!useImmediate) {
    //             qr = registers->read(binaryOperand1);
    //             addThis = qr->result;
    //             delete qr;
    //         }
    //         qr = registers->read(binaryOperand2);
    //         QVector<Value> destinationContents = qr->result;
    //         delete qr;
    //         if(addThis.size() == destinationContents.size()) {
    //             // Nice!  size match
    //             for(int i = 0; i < addThis.size(); i++) {
    //                 if(conditionVector.at(i)) {
    //                     destinationContents[i].i += addThis[i].i;
    //                 }
    //             }
    //         }
    //         else if(addThis.size() == 1){
    //             // scalar to vector incrememtation.
    //             for(int i = 0; i < addThis.size(); i++) {
    //                 if(conditionVector.at(i)) {
    //                     destinationContents[i].i += addThis[0].i;
    //                 }
    //             }
    //         }
    //         // Write back
    //         registers->write(&destinationContents, binaryOperand2);
    //         break;
    //     }
    //     case AND: {
    //         QVector<Value> addThis;
    //         value.i = binaryOperand1;
    //         addThis.push_back(value);
    //         if(!useImmediate) {
    //             qr = registers->read(binaryOperand1);
    //             addThis = qr->result;
    //             delete qr;
    //         }
    //         qr = registers->read(binaryOperand2);
    //         QVector<Value> destinationContents = qr->result;
    //         delete qr;
    //         if(addThis.size() == destinationContents.size()) {
    //             // Nice!  size match
    //             for(int i = 0; i < addThis.size(); i++) {
    //                 if(conditionVector.at(i)) {
    //                     destinationContents[i].i &= addThis[i].i;
    //                 }
    //             }
    //         }
    //         else if(addThis.size() == 1){
    //             // scalar to vector incrememtation.
    //             for(int i = 0; i < addThis.size(); i++) {
    //                 if(conditionVector.at(i)) {
    //                     destinationContents[i].i &= addThis[0].i;
    //                 }
    //             }
    //         }
    //         // Write back
    //         registers->write(&destinationContents, binaryOperand2);
    //         break;
    //     }
    //     case ARR: {
    //         if(conditionVector.at(0)) {
    //             qr = registers->read(binaryOperand1);
    //             QVector<Value> vs = qr->result;
    //             delete qr;
    //             qr = registers->read(binaryOperand2);
    //             QVector<Value> vd = qr->result;
    //             delete qr;
    //             QVector<Value> result = vs;
    //             if(vs.size() == vd.size() && vs.size() != 1) {
    //                 // 1-1 mapping, good to arrange!
    //                 for(int i = 0; i < vs.size(); i++) {
    //                     if(vs[i].i < vd.size() && vs[i].i >= 0) {
    //                         result[i] = vd.at(vs.at(i).i);
    //                     }
    //                 }
    //             }
    //             // Write back
    //             registers->write(&result, binaryOperand2);
    //         }
    //         break;
    //     }
    //
    //     case B: {
    //         if(conditionVector.at(0)) {
    //             pc = unaryOperand;
    //         }
    //         break;
    //     }
    //     case CMP: {
    //         if(conditionVector.at(0)) {
    //             value.i = binaryOperand1;
    //             QVector<Value> arg1;
    //             arg1.push_back(value);
    //             if(!useImmediate) {
    //                 qr = registers->read(binaryOperand1);
    //                 arg1 = qr->result;
    //                 delete qr;
    //             }
    //             qr = registers->read(binaryOperand2);
    //             QVector<Value> arg2 = qr->result;
    //             delete qr;
    //             if(arg1.size() == arg2.size()) {
    //                 // Nice!  size match
    //                 for(int i = 0; i < arg1.size(); i++) {
    //                     registers->write(arg1[i].i == arg2[i].i, Register::flags+i);//TODO 0
    //                     registers->write(arg1[i].i != arg2[i].i, Register::flags+i);//TODO 1
    //                     registers->write(arg1[i].i <= arg2[i].i, Register::flags+i);//TODO 10
    //                     registers->write(arg1[i].i >= arg2[i].i, Register::flags+i);//TODO 11
    //                     registers->write(arg1[i].i  < arg2[i].i, Register::flags+i);//TODO 12
    //                     registers->write(arg1[i].i  > arg2[i].i, Register::flags+i);//TODO 13
    //                 }
    //             }
    //             else if(arg1.size() == 1){
    //                 // scalar to vector incrememtation.
    //                 for(int i = 0; i < arg1.size(); i++) {
    //                     registers->write(arg1[0].i == arg2[i].i, Register::flags+i);//TODO 0
    //                     registers->write(arg1[0].i != arg2[i].i, Register::flags+i);//TODO 1
    //                     registers->write(arg1[0].i <= arg2[i].i, Register::flags+i);//TODO 10
    //                     registers->write(arg1[0].i >= arg2[i].i, Register::flags+i);//TODO 11
    //                     registers->write(arg1[0].i <  arg2[i].i, Register::flags+i);//TODO 12
    //                     registers->write(arg1[0].i >  arg2[i].i, Register::flags+i);//TODO 13
    //                 }
    //             }
    //         }
    //         break;
    //     }
    //     case CPY: {
    //         QVector<Value> placeThis;
    //         value.i = binaryOperand1;
    //         placeThis.push_back(value);
    //         if(!useImmediate) {
    //             qr = registers->read(binaryOperand1);
    //             placeThis = qr->result;
    //             delete qr;
    //         }
    //         qr = registers->read(binaryOperand2);
    //         QVector<Value> destinationContents = qr->result;
    //         delete qr;
    //         if(placeThis.size() == destinationContents.size()) {
    //             // Nice!  size match
    //             for(int i = 0; i < placeThis.size(); i++) {
    //                 if(conditionVector.at(i)) {
    //                     destinationContents[i] = placeThis[i];
    //                 }
    //             }
    //         }
    //         else if(placeThis.size() == 1){
    //             // scalar to vector incrememtation.
    //             for(int i = 0; i < placeThis.size(); i++) {
    //                 if(conditionVector.at(i)) {
    //                     destinationContents[i] = placeThis[0];
    //                 }
    //             }
    //         }
    //         registers->write(&destinationContents, binaryOperand2);
    //         break;
    //     }
    //     case LOD: {
    //         if(conditionVector.at(0)) {
    //             QVector<Value> memAddr;
    //             value.i = binaryOperand1;
    //             memAddr.push_back(value);
    //             if(!useImmediate) {
    //                 qr = registers->read(binaryOperand1);
    //                 memAddr = qr->result;
    //                 delete qr;
    //             }
    //             qr = registers->read(binaryOperand2);
    //             QVector<Value> regContents = qr->result;
    //             delete qr;
    //             // Fill reg with stuff read from memory.
    //             qr = memory->getDataAccess()->read(memAddr.at(0).asUInt, regContents.size());
    //             registers->write(&qr->result, binaryOperand2);
    //             delete qr;
    //         }
    //         break;
    //     }
    //     case STO: {
    //         if(conditionVector.at(0)) {
    //             QVector<Value> memAddr;
    //             value.i = binaryOperand1;
    //             memAddr.push_back(value);
    //             if(!useImmediate) {
    //                 qr = registers->read(binaryOperand1);
    //                 memAddr = qr->result;
    //                 delete qr;
    //             }
    //             qr = registers->read(binaryOperand2);
    //             QVector<Value> regContents = qr->result;
    //             delete qr;
    //             // Send the regContents to memory.
    //             memory->getDataAccess()->write(&regContents, memAddr.at(0).asUInt);
    //         }
    //         break;
    //     }
    //    default: {
    //         break;
    //    }
    // }
    // // pc is now determined fully.
    /* registers->write(pc, Register::PC); */
}
void Baseline::stop(){
    //dummy
}
