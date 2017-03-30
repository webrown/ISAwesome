#ifndef WRITE_VECTOR_ELEMENT_OPERATION_H
#define WRITE_VECTOR_ELEMENT_OPERATION_H
#include "../memory/Register.h"
#include "TernaryOperation.h"
class WriteVectorElementOperation : public TernaryOperation{
    public:
        static WriteVectorElementOperation singleton;
        void decodeOperation(Register *registers, Value arg1, Value arg2, Value arg3);
};
#endif
