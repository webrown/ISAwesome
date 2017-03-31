#include "TernaryOperation.h"
#include "../computer/Architecture.h"
#include <QDebug>

void TernaryOperation::decodeOperation(Register *registers, Value arg1, Value arg2, Value arg3) {
    (void) registers;
    (void) arg1;
    (void) arg2;
    (void) arg3;
};

void TernaryOperation::decode(Register *registers, bool arg1IsImmediate, unsigned int arg1, bool arg2IsImmediate, unsigned int arg2, unsigned int arg3) {
    Value arg1Value;
    Value arg2Value;
    Value arg3Value;
    arg1Value.asUInt = arg1;
    arg2Value.asUInt = arg2;
    arg3Value.asUInt = arg3;

    //if(!arg1IsImmediate && Register::indexExists(arg1) && Register::isScalarIndex(arg1)) {
    (void) arg1IsImmediate;
    if(Register::indexExists(arg1) && Register::isScalarIndex(arg1)) {
        arg1Value = registers->read(arg1);
    }

    if(!arg2IsImmediate && Register::indexExists(arg2) && Register::isScalarIndex(arg2)) {
        arg2Value = registers->read(arg2);
    }

    // All values substituted, ready to roll!
    decodeOperation(registers, arg1Value, arg2Value, arg3Value);
}

