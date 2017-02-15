#ifndef MACHINECODE_H
#define MACHINECODE_H
#include <string>
#include <vector>

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
