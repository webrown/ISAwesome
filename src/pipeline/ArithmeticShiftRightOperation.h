#ifndef ARITHMETICSHIFTRIGHT_OPERATION_H
#define ARITHMETICSHIFTRIGHT_OPERATION_H
#include "ArithmeticOperation.h"
class ArithmeticShiftRightOperation : public ArithmeticOperation{
    public:
        static ArithmeticShiftRightOperation singleton;
        Value scalarOperation(int a, int b);
};
#endif
