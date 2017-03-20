#include "spliceMachineCode.h"

int spliceMachineCode(int machineCode, int startIndex, int endIndex){
    int result = machineCode >> endIndex - (machineCode >> (endIndex+startIndex) << (endIndex+startIndex));
}
