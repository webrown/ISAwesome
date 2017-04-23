#include "ReadVectorElementOperation.h"

ReadVectorElementOperation ReadVectorElementOperation::singleton;

void ReadVectorElementOperation::decodeOperation(Register *registers, Value arg1, Value arg2, Value arg3, int *wait) {
    *wait = 3+1+0+1;
    if(Register::isVectorIndex(arg1.i) && Register::indexExists(arg1.i) && Register::isScalarIndex(arg3.i) && Register::indexExists(arg3.i) && arg2.i >= 0 && arg2.i < VECTOR_SIZE) {
        registers->write(registers->readVector(arg1.i).at(arg2.i), arg3.i);
    }
}
