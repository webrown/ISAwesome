#include "spliceMachineCode.h"
#include <iostream>


string intToBinary(int integer) {
    string result;
    for(int i = 0; i < 32; i++) {
        result += 0x80000000 & integer ? '1' : '0';
        integer <<= 1;
    }
    return result;
}


int spliceMachineCode(int machineCode, int startIndex, int endIndex){
    unsigned int mask = (1 << (endIndex-startIndex+1))-1;
    if(endIndex-startIndex == 31) mask = -1;
    return (machineCode >> startIndex) & mask;
}

