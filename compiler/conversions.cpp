#include "conversions.h"

using namespace std;

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

