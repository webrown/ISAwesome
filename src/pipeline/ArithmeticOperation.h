#ifndef ARITHMETIC_OPERATION_H
#define ARITHMETIC_OPERATION_H
#include "../memory/Register.h"
#include "../memory/Value.h"
#include <QBitArray>
class ArithmeticOperation{
    public:
        static void execute(Register *registers, bool arg1IsImmediate, unsigned int arg1, unsigned int arg2, bool flag, QBitArray flags);
        static Value scalarOperation(int a, int b);
        static Value scalarOperation(float a, float b);
        static Value scalarOperation(float a, int b);
        static Value scalarOperation(int a, float b);
    private:
        static Value scalarOperation(bool arg1IsFloat, bool arg2IsFloat, Value a, Value b);
};
#endif
