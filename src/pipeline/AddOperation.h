#ifndef ADD_OPERATION_H
#define ADD_OPERATION_H
#include "ArithmeticOperation.h"
class AddOperation : public ArithmeticOperation{
    public:
        static AddOperation singleton;
        Value scalarOperation(int a, int b, int *wait);
        Value scalarOperation(float a, float b, int *wait);
};
#endif
