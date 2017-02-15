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

