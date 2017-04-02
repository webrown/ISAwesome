#ifndef DIVIDE_OPERATION_H
#define DIVIDE_OPERATION_H
#include "ArithmeticOperation.h"
class DivideOperation : public ArithmeticOperation{
    public:
        static DivideOperation singleton;
        Value scalarOperation(int a, int b, int *wait);
        Value scalarOperation(float a, float b, int *wait);
};
#endif
