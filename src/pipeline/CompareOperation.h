#ifndef COMPARE_OPERATION_H
#define COMPARE_OPERATION_H
#include "../memory/Register.h"
#include "../memory/Value.h"
class CompareOperation{
    public:
        static CompareOperation singleton;
        void execute(Register *registers, bool arg1IsImmediate, unsigned int arg1, unsigned int arg2);
        Value newFlag(int a, int b);
        Value newFlag(float a, float b);
        Value newFlag(bool arg1IsFloat, bool arg2IsFloat, Value a, Value b, Value oldFlag);
};
#endif
