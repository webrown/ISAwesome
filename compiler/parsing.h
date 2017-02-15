#ifndef PARSING_H
#define PARSING_H
#include <string>
#include <vector>
#include "MachineCode.h"

using namespace std;

string stripComment(string line);

vector<int>* assemblyStringToInt(string assemblyString);

vector<int>* parseInstructionSCondition(string token);

MachineCode* processLine(string line);

#endif
