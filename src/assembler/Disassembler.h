#ifndef DISASSEMBLER_H
#define DISASSEMBLER_H 

#include "InstructionResolver.h"
#include "ConditionResolver.h"


/* Disassembler 
 * 
 *
 */
class Disassembler{
  public: 
    //Constructor
    Disassembler();
    ~Disassembler();

    const InstructionResolver IRS;
    const ConditionResolver CRS;


    QString disassemble(uint instruction);    
};

#endif
