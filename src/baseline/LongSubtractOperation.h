#ifndef LONG_SUBTRACT_OPERATION_H
#define LONG_SUBTRACT_OPERATION_H
#include "LongOperation.h"
class LongSubtractOperation : public LongOperation{
    public:
        static LongSubtractOperation singleton;
        void scalarOperation(int *a, int *b, int *wait);
};
#endif
