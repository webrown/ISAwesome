#ifndef NOT_OPERATION_H
#define NOT_OPERATION_H
#include "ArithmeticOperation.h"
class NotOperation : public ArithmeticOperation{
    public:
        static NotOperation singleton;
        Value scalarOperation(int a, int b);
};
#endif
