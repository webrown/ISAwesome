#include "BinaryInstruction.h"
#include "../Utility.h"
void BinaryInstruction::decode(StageData *sd, Register *r) {
  uint nextInstruction = sd->instruction;
  sd->operand1.i = spliceMachineCode(nextInstruction, 5, 20);
  sd->operand2.i = spliceMachineCode(nextInstruction, 0, 4);
  sd->isImmediate1 = !spliceMachineCode(nextInstruction, 21, 21);
}
