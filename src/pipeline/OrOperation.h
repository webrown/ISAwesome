#ifndef OR_OPERATION_H
#define OR_OPERATION_H
#include "ArithmeticOperation.h"
class OrOperation : public ArithmeticOperation{
    public:
        static OrOperation singleton;
        Value scalarOperation(int a, int b, int *wait);
};
#endif
