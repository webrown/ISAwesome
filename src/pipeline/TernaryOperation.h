#ifndef TERNARY_OPERATION_H
#define TERNARY_OPERATION_H
#include "../memory/Register.h"
#include "../memory/Value.h"
class TernaryOperation{
    public:
        void decode(Register *registers, bool arg1IsImmediate, unsigned int arg1, bool arg2IsImmediate, unsigned int arg2, unsigned int arg3);
        virtual void decodeOperation(Register *registers, Value arg1, Value arg2, Value arg3);
};
#endif
