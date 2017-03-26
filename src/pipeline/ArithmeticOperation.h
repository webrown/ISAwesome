#ifndef ARITHMETIC_OPERATION_H
#define ARITHMETIC_OPERATION_H
#include "../memory/Register.h"
#include "../memory/Value.h"
#include <QBitArray>
class ArithmeticOperation{
    public:
        void execute(Register *registers, bool arg1IsImmediate, unsigned int arg1, unsigned int arg2, bool flag, QBitArray flags);
        virtual Value scalarOperation(int a, int b);
        virtual Value scalarOperation(float a, float b);
        virtual Value scalarOperation(float a, int b);
        virtual Value scalarOperation(int a, float b);
    private:
        Value scalarOperation(bool arg1IsFloat, bool arg2IsFloat, Value a, Value b);
};
#endif
