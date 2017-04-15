#ifndef NOR_OPERATION_H
#define NOR_OPERATION_H
#include "ArithmeticOperation.h"
class NorOperation : public ArithmeticOperation{
    public:
        static NorOperation singleton;
        Value scalarOperation(int a, int b, int *wait);
};
#endif
