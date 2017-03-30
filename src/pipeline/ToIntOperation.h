#ifndef TOINT_OPERATION_H
#define TOINT_OPERATION_H
#include "ArithmeticOperation.h"
class ToIntOperation : public ArithmeticOperation{
    public:
        static ToIntOperation singleton;
        Value scalarOperation(int a, int b);
        Value scalarOperation(float a, int b);
        Value scalarOperation(int a, float b);
        Value scalarOperation(float a, float b);
};
#endif
