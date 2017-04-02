#ifndef MOD_OPERATION_H
#define MOD_OPERATION_H
#include "ArithmeticOperation.h"
class ModOperation : public ArithmeticOperation{
    public:
        static ModOperation singleton;
        Value scalarOperation(int a, int b, int *wait);
};
#endif
