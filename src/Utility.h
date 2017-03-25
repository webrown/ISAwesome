#ifndef UTILITY_H
#define UTILITY_H

#include <QString>

using namespace std;
uint toB(QString str);
QString getDocDir();
int spliceMachineCode(int machineCode, int startIndex, int endIndex);
QString intToBinary(int integer);

#endif
