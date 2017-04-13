#ifndef INSTRUCTION_UTIL_H
#define INSTRUCTION_UTIL_H
#include "StageData.h"
#include "../memory/Register.h"
#include "../memory/Value.h"
#include <QVector>

QVector<Value> pipelineDecideValue(Value operand, bool isImmediate, Register *r);


#endif
