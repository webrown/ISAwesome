#include "Baseline.h"
#include "../Utility.h"
#include "PipelineGlobals.h"
#include "../memory/Flag.h"
#include "AddOperation.h"
#include "AndOperation.h"
#include "ArithmeticOperation.h"
#include "ArithmeticShiftLeftOperation.h"
#include "ArithmeticShiftRightOperation.h"
#include "CompareOperation.h"
#include "CopyOperation.h"
#include "DivideOperation.h"
#include "LoadOperation.h"
#include "LogicalShiftLeftOperation.h"
#include "LogicalShiftRightOperation.h"
#include "LongAddOperation.h"
#include "LongMultiplyOperation.h"
#include "LongSubtractOperation.h"
#include "LongOperation.h"
#include "ModOperation.h"
#include "MultiplyOperation.h"
#include "NandOperation.h"
#include "NorOperation.h"
#include "NotOperation.h"
#include "OrOperation.h"
#include "ReadVectorElementOperation.h"
#include "Shift.h"
#include "StoreOperation.h"
#include "SubtractOperation.h"
#include "ToFloatOperation.h"
#include "ToIntOperation.h"
#include "WriteVectorElementOperation.h"
#include "XorOperation.h"
#include <QDebug>

using namespace Flag;
Baseline::Baseline(Register * regs, MemoryStructure *mem){
    this->registers = regs;
    this->memory = mem;
    this->instructionsDone = 0;
    this->cyclesDone = 0;
    this->_waitLeft = 0;
}

Baseline::~Baseline(){
}

void Baseline::init(){
    // Reset PC
    registers->write(0, Register::PC);
    // You aren't waiting for any instructions!
    this->_waitLeft = 0;
}

Status Baseline::run(void){
    cyclesDone++;
    // Bail if you're still waiting for the next instruction to finish.
    _waitLeft--;
    if(_waitLeft > 0) {
        return OKAY;
    }
    // Complete 1 instruction 
    instructionsDone++;
    QueryResult *qr = NULL;
   
    // Get the next instruction address.
    // Get next instruction from memory.
    qr = memory->getInstructionAccess()->read(registers->getPC());
    unsigned int nextInstruction = qr->result.at(0).asUInt;
    delete qr;
    // Move to next instruction address.
    registers->write(registers->getPC()+INSTRUCTION_SIZE, Register::PC);
    // What is instruction type?
    unsigned int opcode = spliceMachineCode(nextInstruction, 22, 27);

    Instruction instructionType;
    if(opcode == toB(QString("000000"))) instructionType     =  B         ;
    if(opcode == toB(QString("000001"))) instructionType    =  BL         ;
    if(opcode == toB(QString("000011"))) instructionType   =  CMP         ;
    if(opcode == toB(QString("000100"))) instructionType   =  CPY         ;
    if(opcode == toB(QString("000101"))) instructionType   =  LOD         ;
    if(opcode == toB(QString("000110"))) instructionType   =  STO         ;
    if(opcode == toB(QString("001000"))) instructionType   =  RVE         ;
    if(opcode == toB(QString("001001"))) instructionType   =  WVE         ;
    if(opcode == toB(QString("001010"))) instructionType   =  MVD         ;
    if(opcode == toB(QString("001011"))) instructionType   =  MVU         ;
    if(opcode == toB(QString("001100"))) instructionType   =  ARR         ;
    if(opcode == toB(QString("001101"))) instructionType   =  SEQ         ;
    if(opcode == toB(QString("001110"))) instructionType   =  SOE         ;
    if(opcode == toB(QString("001111"))) instructionType   =  MOE         ;
    if(opcode == toB(QString("010000"))) instructionType   =  ADD         ;
    if(opcode == toB(QString("010001"))) instructionType  =  ADDS         ;
    if(opcode == toB(QString("010010"))) instructionType   =  ADC         ;
    if(opcode == toB(QString("010011"))) instructionType  =  ADCS         ;
    if(opcode == toB(QString("010100"))) instructionType   =  SUB         ;
    if(opcode == toB(QString("010101"))) instructionType  =  SUBS         ;
    if(opcode == toB(QString("010110"))) instructionType   =  SBC         ;
    if(opcode == toB(QString("010111"))) instructionType  =  SBCS         ;
    if(opcode == toB(QString("011000"))) instructionType   =  MUL         ;
    if(opcode == toB(QString("011001"))) instructionType  =  MULS         ;
    if(opcode == toB(QString("011010"))) instructionType  =  LMUL         ;
    if(opcode == toB(QString("011011"))) instructionType =  LMULS         ;
    if(opcode == toB(QString("011100"))) instructionType   =  DIV         ;
    if(opcode == toB(QString("011101"))) instructionType  =  DIVS         ;
    if(opcode == toB(QString("011110"))) instructionType  =  LDIV         ;
    if(opcode == toB(QString("011111"))) instructionType  =  LDIV         ;
    if(opcode == toB(QString("100000"))) instructionType   =  MOD         ;
    if(opcode == toB(QString("100001"))) instructionType  =  MODS         ;
    if(opcode == toB(QString("101000"))) instructionType   =  LSR         ;
    if(opcode == toB(QString("101001"))) instructionType  =  LSRS         ;
    if(opcode == toB(QString("101010"))) instructionType   =  LSL         ;
    if(opcode == toB(QString("101011"))) instructionType  =  LSLS         ;
    if(opcode == toB(QString("101100"))) instructionType   =  ASL         ;
    if(opcode == toB(QString("101101"))) instructionType  =  ASLS         ;
    if(opcode == toB(QString("101110"))) instructionType   =  ASR         ;
    if(opcode == toB(QString("101111"))) instructionType  =  ASRS         ;
    if(opcode == toB(QString("110000"))) instructionType   =  AND         ;
    if(opcode == toB(QString("110001"))) instructionType  =  ANDS         ;
    if(opcode == toB(QString("110010"))) instructionType  =  NAND         ;
    if(opcode == toB(QString("110011"))) instructionType =  NANDS         ;
    if(opcode == toB(QString("110100"))) instructionType    =  OR         ;
    if(opcode == toB(QString("110101"))) instructionType  =  ORS          ;
    if(opcode == toB(QString("110110"))) instructionType   =  NOR         ;
    if(opcode == toB(QString("110111"))) instructionType  =  NORS         ;
    if(opcode == toB(QString("111000"))) instructionType   =  XOR         ;
    if(opcode == toB(QString("111001"))) instructionType  =  XORS         ;
    if(opcode == toB(QString("111010"))) instructionType   =  NOT         ;
    if(opcode == toB(QString("111011"))) instructionType  =  NOTS         ;
    if(opcode == toB(QString("111100"))) instructionType   =  TOI         ;
    if(opcode == toB(QString("111101"))) instructionType   =  TOF         ;
   
    // What is the flag?
    unsigned int flagCode = spliceMachineCode(nextInstruction, 28, 31);
    FlagType flag;
    if(flagCode ==  0) flag = EQ;
    if(flagCode ==  1) flag = NE;
    if(flagCode ==  2) flag = CS;
    if(flagCode ==  3) flag = CC;
    if(flagCode ==  4) flag = MI;
    if(flagCode ==  5) flag = PL;
    if(flagCode ==  6) flag = VS;
    if(flagCode ==  7) flag = VC;
    if(flagCode ==  8) flag = DZ;
    if(flagCode ==  9) flag = NZ;
    if(flagCode == 10) flag = LE;
    if(flagCode == 11) flag = GE;
    if(flagCode == 12) flag = LT;
    if(flagCode == 13) flag = GT;
    if(flagCode == 14) flag = AL;
    if(flagCode == 15) flag = UN;
   
    // Interpret flag.
    QBitArray conditionVector = has(registers->readFlags(), flag);
    bool conditionScalar = has(registers->readFlag(), flag);
   
    // Determine if operand 1 is an immediate
    int useImmediate = !spliceMachineCode(nextInstruction, 21, 21);
    int useImmediateTernary = !spliceMachineCode(nextInstruction, 14, 14);
   
    // Grab unary operand
    int unaryOperand = spliceMachineCode(nextInstruction, 0, 20);
   
    // Grab binary operands
    int binaryOperand1 = spliceMachineCode(nextInstruction, 5, 20);
    int binaryOperand2 = spliceMachineCode(nextInstruction, 0, 4);
   
    // Grab ternary operands
    int ternaryOperand1 = spliceMachineCode(nextInstruction, 15, 20);
    int ternaryOperand2 = spliceMachineCode(nextInstruction, 8, 13);
    int ternaryOperand3 = spliceMachineCode(nextInstruction, 0, 4);

    qDebug() << "COM: nextInstruction:" << nextInstruction << intToBinary(nextInstruction);
    qDebug() << "COM: nextOpCode:" << opcode << intToBinary(opcode);
   
    // Do what the instruction tells you to.
    switch(instructionType) {
        case ADC: {
            LongAddOperation::singleton.execute(registers, binaryOperand1, binaryOperand2, conditionScalar, conditionVector, &_waitLeft);
            break;
        }
        case ADD:
        case SOE: {
            AddOperation::singleton.execute(registers, useImmediate, binaryOperand1, binaryOperand2, conditionScalar, conditionVector, &_waitLeft);
            break;
        }
        case AND: {
            AndOperation::singleton.execute(registers, useImmediate, binaryOperand1, binaryOperand2, conditionScalar, conditionVector, &_waitLeft);
            break;
        }
        case ARR: {
            _waitLeft = 1;
            if(conditionScalar) {
                _waitLeft = 3;
                // Only fires if both items are vectors and vs must be an int
                if(Register::isVectorIndex(binaryOperand1) && Register::isVectorIndex(binaryOperand2) && !Register::isFloatIndex(binaryOperand1)) {
                    QVector<Value> vs = registers->readVector(binaryOperand1);
                    QVector<Value> vd = registers->readVector(binaryOperand2);
                    QVector<Value> result = vs;
                    for(int i = 0; i < vs.size(); i++) {
                        if(vs[i].i < vd.size() && vs[i].i >= 0) {
                            result[i] = vd.at(vs.at(i).i);
                        }
                    }
                    // Write back
                    registers->write(result, binaryOperand2);
                }
            }
            break;
        }
        case ASL: {
            ArithmeticShiftLeftOperation::singleton.execute(registers, useImmediate, binaryOperand1, binaryOperand2, conditionScalar, conditionVector, &_waitLeft);
            break;
        }
        case ASR: {
            ArithmeticShiftRightOperation::singleton.execute(registers, useImmediate, binaryOperand1, binaryOperand2, conditionScalar, conditionVector, &_waitLeft);
            break;
        }
        case B: {
            _waitLeft = 1;
            if(conditionScalar) {
                registers->write(unaryOperand, Register::PC);
            }
            break;
        }
        case BL: {
            _waitLeft = 1;
            if(conditionScalar) {
                _waitLeft = 2;
                // Is this register valid for reading?
                if(Register::indexExists(unaryOperand) && Register::isScalarIndex(unaryOperand)) {
                    // Grab the things you want to write.
                    Value oldPC = registers->read(Register::PC);
                    Value newPC = registers->read(unaryOperand);
                    // Link back.
                    registers->write(oldPC, Register::LR);
                    // Move PC
                    registers->write(newPC, Register::PC);
                }
            }
            break;
        }
        case CMP: {
            _waitLeft = 1;
            if(conditionScalar) {
                CompareOperation::singleton.execute(registers, useImmediate, binaryOperand1, binaryOperand2, &_waitLeft);
            }
            break;
        }
        case CPY: {
            CopyOperation::singleton.execute(registers, useImmediate, binaryOperand1, binaryOperand2, conditionScalar, conditionVector, &_waitLeft);
            break;
        }
        case DIV: {
            DivideOperation::singleton.execute(registers, useImmediate, binaryOperand1, binaryOperand2, conditionScalar, conditionVector, &_waitLeft);
            break;
        }
        case LMUL: {
            LongMultiplyOperation::singleton.execute(registers, binaryOperand1, binaryOperand2, conditionScalar, conditionVector, &_waitLeft);
            break;
        }
        case LOD: {
            _waitLeft = 1;
            if(conditionScalar) {
                LoadOperation::singleton.memory(registers, memory, useImmediate, binaryOperand1, binaryOperand2, &_waitLeft);
            }
            break;
        }
        case LSL: {
            LogicalShiftLeftOperation::singleton.execute(registers, useImmediate, binaryOperand1, binaryOperand2, conditionScalar, conditionVector, &_waitLeft);
            break;
        }
        case LSR: {
            LogicalShiftRightOperation::singleton.execute(registers, useImmediate, binaryOperand1, binaryOperand2, conditionScalar, conditionVector, &_waitLeft);
            break;
        }
        case MOD: {
            ModOperation::singleton.execute(registers, useImmediate, binaryOperand1, binaryOperand2, conditionScalar, conditionVector, &_waitLeft);
            break;
        }
        case MUL:
        case MOE: {
            MultiplyOperation::singleton.execute(registers, useImmediate, binaryOperand1, binaryOperand2, conditionScalar, conditionVector, &_waitLeft);
            break;
        }
        case MVD: {
            _waitLeft = 1;
            if(conditionScalar) {
                Shift::executeDown(registers, useImmediate, binaryOperand1, binaryOperand2, &_waitLeft);
            }
            break;
        }
        case MVU: {
            _waitLeft = 1;
            if(conditionScalar) {
                Shift::executeUp(registers, useImmediate, binaryOperand1, binaryOperand2, &_waitLeft);
            }
            break;
        }
        case NAND: {
            NandOperation::singleton.execute(registers, useImmediate, binaryOperand1, binaryOperand2, conditionScalar, conditionVector, &_waitLeft);
            break;
        }
        case NOR: {
            NorOperation::singleton.execute(registers, useImmediate, binaryOperand1, binaryOperand2, conditionScalar, conditionVector, &_waitLeft);
            break;
        }
        case NOT: {
            NotOperation::singleton.execute(registers, useImmediate, binaryOperand1, binaryOperand2, conditionScalar, conditionVector, &_waitLeft);
            break;
        }
        case OR: {
            OrOperation::singleton.execute(registers, useImmediate, binaryOperand1, binaryOperand2, conditionScalar, conditionVector, &_waitLeft);
            break;
        }
        case RVE: {
            _waitLeft = 1;
            if(conditionScalar) {
                ReadVectorElementOperation::singleton.decode(registers, useImmediate, ternaryOperand1, useImmediateTernary, ternaryOperand2, ternaryOperand3, &_waitLeft);
            }
            break;
        }
        case SBC: {
            LongSubtractOperation::singleton.execute(registers, binaryOperand1, binaryOperand2, conditionScalar, conditionVector, &_waitLeft);
            break;
        }
        case SEQ: {
            _waitLeft = 1;
            // SEQ makes no sense with scalars or immediates
            if(!Register::isScalarIndex(unaryOperand) && Register::indexExists(unaryOperand)) {
                QVector<Value> newVector;
                for(int i = 0; i < registers->readVector(unaryOperand).size(); i++) {
                    if(conditionVector.at(i)) {
                        Value v;
                        v.i = i;
                        newVector.push_back(v);
                    }
                    else {
                        // Don't replace unflagged indexes.
                        newVector.push_back(registers->readVector(unaryOperand).at(i));
                    }
                }
                registers->writeVector(newVector, unaryOperand);
            }
            break;
        }
        case STO: {
            _waitLeft = 1;
            if(conditionScalar) {
                StoreOperation::singleton.memory(registers, memory, useImmediate, binaryOperand1, binaryOperand2, &_waitLeft);
            }
            break;
        }
        case SUB: {
            SubtractOperation::singleton.execute(registers, useImmediate, binaryOperand1, binaryOperand2, conditionScalar, conditionVector, &_waitLeft);
            break;
        }
        case TOF: {
            ToFloatOperation::singleton.execute(registers, useImmediate, binaryOperand1, binaryOperand2, conditionScalar, conditionVector, &_waitLeft);
            break;
        }
        case TOI: {
            ToIntOperation::singleton.execute(registers, useImmediate, binaryOperand1, binaryOperand2, conditionScalar, conditionVector, &_waitLeft);
            break;
        }
        case XOR: {
            XorOperation::singleton.execute(registers, useImmediate, binaryOperand1, binaryOperand2, conditionScalar, conditionVector, &_waitLeft);
            break;
        }
        case WVE: {
            if(conditionScalar) {
                WriteVectorElementOperation::singleton.decode(registers, useImmediate, ternaryOperand1, useImmediateTernary, ternaryOperand2, ternaryOperand3, &_waitLeft);
            }
            break;
        }
        default: {
            qDebug() << "OPCODE " << instructionType << " unrecognized.";
            _waitLeft = 1;
            break;
        }
     }
     // Yay!  no error!  Well done!
     return OKAY;
}
void Baseline::stop(){
    //dummy
}
