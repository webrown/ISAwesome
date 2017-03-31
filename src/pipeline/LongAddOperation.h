#ifndef LONG_ADD_OPERATION_H
#define LONG_ADD_OPERATION_H
#include "LongOperation.h"
class LongAddOperation : public LongOperation{
    public:
        static LongAddOperation singleton;
        void scalarOperation(int *a, int *b);
};
#endif
