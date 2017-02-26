#include "utility.h"

using namespace std;

string uppercase(string input) {
  for(size_t i = 0; i < input.length(); i++) {
    if('a' <= input[i] && input[i] <= 'z') {
      input[i] = input[i] + ('A'-'a');
    }
  }
  return input;
}

vector<string> split(string line, char delimeter) {
  vector<string> result;
  size_t index = 0;
  size_t pos = line.find(delimeter);
  while(pos != string::npos) {
    if(pos > index) result.push_back(line.substr(index, pos-index));
    index = ++pos;
    pos = line.find(delimeter, pos);
  }
  if(line.length() > index) result.push_back(line.substr(index, line.length()));
  return result;
}

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

