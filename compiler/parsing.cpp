#include <iostream>
#include <string>
#include <vector>
#include "utility.h"
#include "conversions.h"
#include "MachineCode.h"
#include "parsing.h"

using namespace std;

string stripComment(string line) {
  line = split(line, ';').at(0);
  return line;
}

vector<int>* assemblyStringToInt(string assemblyString) {
  // Hammer-function for converting all arguments to numbers.
  // Returns two outputs:
  // -int value
  // -flag to indicate if this is an immediate
  vector<int>* result = new vector<int>();
  if(assemblyString.at(0) == 'R') {
    // Register
    result->push_back(stoi(assemblyString.substr(1)));
    result->push_back(0);
    return result;
  }
  if(assemblyString.at(0) == 'V') {
    // Vector
    result->push_back(16+(assemblyString.at(1)-'A'));
    result->push_back(0);
    return result;
  }
  if(assemblyString.at(0) == '#') {
    // Immediate
    if(assemblyString.substr(1,2) == "0X") {
      // Hex mode
      result->push_back(stoi(assemblyString.substr(3), NULL, 16));
    } else {
      // Maybe a decimal?
      result->push_back(stoi(assemblyString));
    }
    result->push_back(0);
    return result;
  }
  return NULL;
}

vector<int>* parseInstructionSCondition(string token) {
  // Retern a vector that has:
  // -Flag code
  // -opcode
  // -which operand decides the L bit? (-1 means none.)
  // -Then an alternation between start/end indexes for where tokens should be
  //  stored.
  // Much refactoring needed here.
  vector<int>* result = new vector<int>();
  if(token == "SEQ") {
    result->push_back(binaryStringToInt("1110"));
    result->push_back(binaryStringToInt("001101"));
    result->push_back(1);
    result->push_back(0);
    result->push_back(20);
  }
  else if(token == "CMP") {
    result->push_back(binaryStringToInt("1110"));
    result->push_back(binaryStringToInt("000010"));
    result->push_back(1);
    result->push_back(5);
    result->push_back(20);
    result->push_back(0);
    result->push_back(4);
  }
  else if(token == "CPY") {
    result->push_back(binaryStringToInt("1110"));
    result->push_back(binaryStringToInt("000100"));
    result->push_back(1);
    result->push_back(5);
    result->push_back(20);
    result->push_back(0);
    result->push_back(4);
  }
  else if(token == "LODLE") {
    result->push_back(binaryStringToInt("1010"));
    result->push_back(binaryStringToInt("000101"));
    result->push_back(1);
    result->push_back(5);
    result->push_back(20);
    result->push_back(0);
    result->push_back(4);
  }
  else {
    // Unrecognized instruction name
    return NULL;
  }
  return result;
}

MachineCode* processLine(string line) {
  const bool debug = 0;
  MachineCode* result = new MachineCode();
  line = uppercase(line);
  line = stripComment(line);
  if(debug) cout << "line:" << line << endl;
  vector<string> tokens = split(line, ' ');
  // Bail if there's nothing here.
  if(tokens.size() == 0) return NULL;
  // Grab the opcode.
  string instruction = tokens.at(0);
  vector<int>* isc = parseInstructionSCondition(instruction);
  if(isc) {
    result->writeInt(isc->at(0), 28, 31);
    result->writeInt(isc->at(1), 22, 27);
    // Put in arguments.
    for(size_t i = 1; i < tokens.size(); i++) {
      vector<int>* asti = assemblyStringToInt(tokens.at(i));
      if(asti) {
        result->writeInt(asti->at(0), isc->at(3+2*(i-1)), isc->at(3+2*(i-1)+1));
        if(i == isc->at(2)) {
          // This is the "Large" operand.
          result->writeInt(asti->at(1), 21, 21);
        }
      }
      else {
        cout << "I don't know what " << tokens.at(i) << " is." << endl;
      }
    }
  }
  else {
    cout << "I don't know how to " << instruction << "." << endl;
  }
  return result;
}

