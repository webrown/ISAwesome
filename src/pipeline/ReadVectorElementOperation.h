#ifndef READ_VECTOR_ELEMENT_OPERATION_H
#define READ_VECTOR_ELEMENT_OPERATION_H
#include "../memory/Register.h"
#include "TernaryOperation.h"
class ReadVectorElementOperation : public TernaryOperation{
    public:
        static ReadVectorElementOperation singleton;
        void decodeOperation(Register *registers, Value arg1, Value arg2, Value arg3, int *wait);
};
#endif
