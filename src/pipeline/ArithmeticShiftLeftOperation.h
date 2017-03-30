#ifndef ARITHMETICSHIFTLEFT_OPERATION_H
#define ARITHMETICSHIFTLEFT_OPERATION_H
#include "ArithmeticOperation.h"
class ArithmeticShiftLeftOperation : public ArithmeticOperation{
    public:
        static ArithmeticShiftLeftOperation singleton;
        Value scalarOperation(int a, int b);
};
#endif
