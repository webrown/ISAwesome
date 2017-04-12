#include "TernaryInstruction.h"
#include "../Utility.h"
void TernaryInstruction::decode(StageData *sd, Register *r) {
  uint nextInstruction = sd->instruction;
  sd->operand1.i = spliceMachineCode(nextInstruction, 15, 20);
  sd->operand2.i = spliceMachineCode(nextInstruction, 8, 13);
  sd->operand3.i = spliceMachineCode(nextInstruction, 0, 4);
  sd->isImmediate1 = !spliceMachineCode(nextInstruction, 21, 21);
  sd->isImmediate2 = !spliceMachineCode(nextInstruction, 14, 14);
}
