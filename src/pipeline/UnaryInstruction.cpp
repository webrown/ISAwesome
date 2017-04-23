#include "UnaryInstruction.h"
#include "../Utility.h"
void UnaryInstruction::decode(StageData *currData, Register * r, int *wait) {
  *wait = 1;
  uint vvv = currData->instruction;
  currData->operand1.i = spliceMachineCode(vvv, 0, 20);
}
