#ifndef PARSING_H
#define PARSING_H
#include <iostream>
#include <string>
#include <vector>
#include "utility.h"
#include "conversions.h"
#include "MachineCode.h"

using namespace std;

string stripComment(string line);

vector<int>* assemblyStringToInt(string assemblyString);

vector<int>* parseInstructionSCondition(string token);

MachineCode* processLine(string line);

#endif
