#ifndef XOR_OPERATION_H
#define XOR_OPERATION_H
#include "ArithmeticOperation.h"
class XorOperation : public ArithmeticOperation{
    public:
        static XorOperation singleton;
        Value scalarOperation(int a, int b);
};
#endif
