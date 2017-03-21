#include "Disassembler.h"

#define FLAG_BIT        toB("11110000000000000000000000000000")
#define OPCODE_BIT      toB("00001111110000000000000000000000")
#define ARG_BIT         toB("00000000001111111111111111111111")

Disassembler::Disassembler(){
}
Disassembler::~Disassembler(){
}

QString Disassembler::disassemble(uint instruction){
    qDebug() << "Disassemble: " << QString::number(instruction, 2).rightJustified(32,'0');
    uint flag = (instruction & FLAG_BIT) >> 28;
    uint opcode = (instruction & OPCODE_BIT) >> 22;
    uint arg = (instruction & ARG_BIT);
    qDebug() << "Splitted: " <<QString::number(flag, 2).rightJustified(4, '0') << "\t" 
        <<QString::number(opcode, 2).rightJustified(6,'0') << "\t" 
        <<QString::number(arg, 2).rightJustified(22,'0');
    QString result;
    if(CRS.condTable.contains(flag)){
        result += CRS.condTable[flag] + " ";
    }
    else{
        result += "?? ";
    }
    
    if(IRS.opcodeTable.contains(opcode)){
        InstructionDefinition* def = IRS.opcodeTable[opcode];
        result += def->name + " ";
        result += def->unparse(arg).unparsed;
    }
    else{
        result += "NOP ";
    }
    qDebug() << "Disassembled: " << result;

    return result;
}
