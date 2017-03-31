#ifndef LONG_OPERATION_H
#define LONG_OPERATION_H
#include "../memory/Register.h"
#include "../memory/Value.h"
#include <QBitArray>
class LongOperation{
    public:
        void execute(Register *registers, unsigned int arg1, unsigned int arg2, bool flag, QBitArray flags);
        virtual void scalarOperation(int *a, int *b);
};
#endif
