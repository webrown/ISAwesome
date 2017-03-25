#ifndef COMPARE_OPERATION_H
#define COMPARE_OPERATION_H
#include "../memory/Register.h"
#include "../memory/Value.h"
class CompareOperation{
    public:
        static void execute(Register *registers, bool arg1IsImmediate, unsigned int arg1, unsigned int arg2);
        static Value newFlag(int a, int b);
        static Value newFlag(float a, float b);
    private:
        static Value newFlag(bool arg1IsFloat, bool arg2IsFloat, Value a, Value b, Value oldFlag);
};
#endif
