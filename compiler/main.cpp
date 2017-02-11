#include <iostream>
#include <string>
#include <vector>

using namespace std;

const bool debug = 1;

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

string stripComment(string line) {
  line = split(line, ';').at(0);
  return line;
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

class MachineCode {
  public:
    vector<bool> bits;
    MachineCode() {
      // There are 32 bits per instruction.
      for(int i = 0; i < 32; i++)
        bits.push_back(true);
    }
    string getASCIIForm() {
      string result = "";
      for(char i = 0; i < bits.size(); i+= 8) {
        result += boolsToChar(bits, i);
      }
      return result;
    }
    string getBooleanForm() {
      string result = "";
      for(char i = bits.size()-1; i >= 0; i--) {
        result += bits.at(i) ? "1" : "0";
      }
      return result;
    }
    void writeInt(int value, int start, int end) {
      for(int i = start; i < end+1; i++) {
        bits[i] = value & 1; // Write bit in ones place.
        value >>= 1; // Shift the value over by 1.
      }
    }
};

MachineCode* processLine(string line) {
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

int main() {
  string line;
  while(getline(cin, line)) {
    MachineCode* mc = processLine(line);
    if(mc) {
      if(debug) {
        cout << "bits:" << mc->getBooleanForm() << endl;
        cout << "out:" << mc->getASCIIForm() << endl;
      }
      else {
        cout << mc->getASCIIForm();
      }
    }
  }
  return 0;
}

