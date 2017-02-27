#include "instructionResolver.h"
#include "memoryInstruction.h"

InstructionResolver::InstructionResolver(){
    //load memory instructions
    MemoryInstructionLoader::load(nameMap, opcodeMap);
}
InstructionResolver::~InstructionResolver(){
}

const Instruction* InstructionResolver::resolveWithName(QString name){
    if(nameMap.contains(name)){
        return nameMap[name];
    }
    else{
        return NULL;
    }
}

const Instruction* InstructionResolver::resolveWithOpcode(uint opcode){
    if(opcodeMap.contains(opcode)){
        return opcodeMap[opcode];
    }
    else{
        return NULL;
    }
}
