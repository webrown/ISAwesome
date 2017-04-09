#ifndef NAND_OPERATION_H
#define NAND_OPERATION_H
#include "ArithmeticOperation.h"
class NandOperation : public ArithmeticOperation{
    public:
        static NandOperation singleton;
        Value scalarOperation(int a, int b, int *wait);
};
#endif
