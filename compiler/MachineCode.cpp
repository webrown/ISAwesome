#include "conversions.h"
#include "MachineCode.h"

using namespace std;

MachineCode::MachineCode() {
  // There are 32 bits per instruction.
  for(int i = 0; i < 32; i++)
    bits.push_back(true);
}

string MachineCode::getASCIIForm() {
  string result = "";
  for(char i = 0; i < bits.size(); i+= 8) {
    result += boolsToChar(bits, i);
  }
  return result;
}

string MachineCode::getBooleanForm() {
  string result = "";
  for(char i = bits.size()-1; i >= 0; i--) {
    result += bits.at(i) ? "1" : "0";
  }
  return result;
}

void MachineCode::writeInt(int value, int start, int end) {
  for(int i = start; i < end+1; i++) {
    bits[i] = value & 1; // Write bit in ones place.
    value >>= 1; // Shift the value over by 1.
  }
}

