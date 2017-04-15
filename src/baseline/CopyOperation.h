#ifndef COPY_OPERATION_H
#define COPY_OPERATION_H
#include "ArithmeticOperation.h"
class CopyOperation : public ArithmeticOperation{
    public:
        static CopyOperation singleton;
        Value scalarOperation(int a, int b, int *wait);
        Value scalarOperation(float a, float b, int *wait);
        Value scalarOperation(float a, int b, int *wait);
        Value scalarOperation(int a, float b, int *wait);
};
#endif
