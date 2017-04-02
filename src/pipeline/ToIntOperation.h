#ifndef TOINT_OPERATION_H
#define TOINT_OPERATION_H
#include "ArithmeticOperation.h"
class ToIntOperation : public ArithmeticOperation{
    public:
        static ToIntOperation singleton;
        Value scalarOperation(int a, int b, int *wait);
        Value scalarOperation(float a, int b, int *wait);
        Value scalarOperation(int a, float b, int *wait);
        Value scalarOperation(float a, float b, int *wait);
};
#endif
