#ifndef SHIFT_OPERATION_H
#define SHIFT_OPERATION_H
#include "../memory/Register.h"
class Shift {
  public:
    static void executeUp(Register *registers, bool arg1Immediate, int arg1, int arg2, int *wait);
    static void executeDown(Register *registers, bool arg1Immediate, int arg1, int arg2, int *wait);
  private:
    static void execute(Register *registers, bool arg1Immediate, int arg1, int arg2, int scale, int *wait);
};
#endif
