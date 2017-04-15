#ifndef AND_OPERATION_H
#define AND_OPERATION_H
#include "ArithmeticOperation.h"
class AndOperation : public ArithmeticOperation{
    public:
        static AndOperation singleton;
        Value scalarOperation(int a, int b, int *wait);
};
#endif
