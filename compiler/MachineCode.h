#ifndef MACHINECODE_H
#define MACHINECODE_H
#include <iostream>
#include <string>
#include <vector>
#include "utility.h"
#include "conversions.h"

using namespace std;

class MachineCode {
  public:
    vector<bool> bits;
    MachineCode();
    string getASCIIForm();
    string getBooleanForm();
    void writeInt(int value, int start, int end);
};

#endif
