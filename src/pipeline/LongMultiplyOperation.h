#ifndef LONG_MULTIPLY_OPERATION_H
#define LONG_MULTIPLY_OPERATION_H
#include "LongOperation.h"
class LongMultiplyOperation : public LongOperation{
    public:
        static LongMultiplyOperation singleton;
        void scalarOperation(int *a, int *b);
};
#endif
