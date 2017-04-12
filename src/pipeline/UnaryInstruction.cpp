#include "UnaryInstruction.h"
void UnaryInstruction::decode(StageData *currData, Register * r) {
  uint vvv = currData->instruction;
  currData->operand1 = {vvv & ((1<<23)-1)};
}
