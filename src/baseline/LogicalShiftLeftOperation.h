#ifndef LOGICALSHIFTLEFT_OPERATION_H
#define LOGICALSHIFTLEFT_OPERATION_H
#include "ArithmeticOperation.h"
class LogicalShiftLeftOperation : public ArithmeticOperation{
    public:
        static LogicalShiftLeftOperation singleton;
        Value scalarOperation(int a, int b, int *wait);
};
#endif
