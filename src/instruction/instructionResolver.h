#ifndef INSTRUCTIONRESOLVER_H
#define INSTRUCTIONRESOLVER_H

#include <QMap>
#include "instruction.h"
class InstructionResolver{
    public:
        InstructionResolver();
        ~InstructionResolver();
        QMap<QString, Instruction*> nameMap;
        QMap<uint, Instruction*> opcodeMap;
        const Instruction* resolveWithName(QString name);
        const Instruction* resolveWithOpcode(uint opcode);
};


#endif
