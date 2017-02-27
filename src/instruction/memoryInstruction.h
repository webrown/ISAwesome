#ifndef MEMORYINSTRUCTION_H
#define MEMROYINSTRUCTION_H

#include "instruction.h"
#include <QMap>

class MemoryInstructionLoader{
    public:
        static void load(QMap<QString, Instruction*> nameMap, QMap<uint, Instruction*> opcodeMap);
};

#endif
