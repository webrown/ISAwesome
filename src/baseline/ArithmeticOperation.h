#ifndef ARITHMETIC_OPERATION_H
#define ARITHMETIC_OPERATION_H
#include "../memory/Register.h"
#include "../memory/Value.h"
#include <QBitArray>
class ArithmeticOperation{
    public:
        void execute(Register *registers, bool arg1IsImmediate, unsigned int arg1, unsigned int arg2, bool flag, QBitArray flags, int *wait);
        virtual Value scalarOperation(int a, int b, int *wait);
        virtual Value scalarOperation(float a, float b, int *wait);
        virtual Value scalarOperation(float a, int b, int *wait);
        virtual Value scalarOperation(int a, float b, int *wait);
    private:
        Value scalarOperation(bool arg1IsFloat, bool arg2IsFloat, Value a, Value b, int *wait);
};
#endif
