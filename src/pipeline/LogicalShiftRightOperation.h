#ifndef LOGICALSHIFTRIGHT_OPERATION_H
#define LOGICALSHIFTRIGHT_OPERATION_H
#include "ArithmeticOperation.h"
class LogicalShiftRightOperation : public ArithmeticOperation{
    public:
        static LogicalShiftRightOperation singleton;
        Value scalarOperation(int a, int b);
};
#endif
