#include <iostream>
#include <string>
#include <vector>
#include "utility.h"
#include "conversions.h"
#include "MachineCode.h"
#include "parsing.h"

using namespace std;

int main() {
  const bool debug = 0;
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

