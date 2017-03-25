#include "Utility.h"
#include <QStandardPaths>


using namespace std;

uint toB(QString str){
  bool ok;
  return str.toUInt(&ok, 2);
}

QString getDocDir(){
    return QStandardPaths::locate(QStandardPaths::DocumentsLocation, QString(), QStandardPaths::LocateDirectory);
}

QString intToBinary(int integer) {
    QString result;
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


/*
int binaryStringToInt(string binaryString) {
  char result = 0;
  for(char i = 0; i < binaryString.length(); i++){
    if(binaryString.at(i) != '0') {
      result |= (1 << i);
    }
  }
  return result;
}

char boolsToChar(vector<bool> bools, int startIndex) {
  // Converts region of bools array from startIndex to startIndex+8 into char.
  char result = 0;
  int boolsIter = startIndex;
  for(char resultIter = 0; resultIter < 8; resultIter++){
    if(bools.at(boolsIter) == 1) {
      result |= (1 << resultIter);
    }
    boolsIter++;
  }
  return result;
}
*/
