#include "WriteVectorElementOperation.h"
#include <QVector>

WriteVectorElementOperation WriteVectorElementOperation::singleton;

void WriteVectorElementOperation::decodeOperation(Register *registers, Value arg1, Value arg2, Value arg3) {
    if(Register::isVectorIndex(arg2.i) && Register::indexExists(arg2.i) && arg3.i >= 0 && arg3.i < VECTOR_SIZE) {
        QVector<Value> vectorContents = registers->readVector(arg2.i);
        vectorContents[arg3.i] = arg1;
        registers->writeVector(vectorContents, arg2.i);
    }
}
