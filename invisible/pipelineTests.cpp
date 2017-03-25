//#include "PipelineGlobals.h"
//#include "Pipeline.h"
#include "../src/pipeline/Baseline.h"
#include "../src/Utility.h"
//#include "StageData.h"

#include <string>
#include <iostream>

using namespace std;

void checkEqual(int a, int b, string description) {
    if(a == b) {
        cout << "PASS: (";
    } else {
        cout << "FAIL: (";
    }
    cout << a << " vs " << b << ")" << description << endl;
}

int main() {
    cout << intToBinary(10).toUtf8().constData() << endl;
    cout << intToBinary(-1).toUtf8().constData() << endl;
    checkEqual(intToBinary(0).size(), 32, "Good intToBinary length");

    // Make sure distance between start and end increases length.
    int allOnes = -1;
    checkEqual(spliceMachineCode(allOnes, 0,0), 1, "1 bit test");
    checkEqual(spliceMachineCode(allOnes, 0,1), 3, "2 bit test");
    checkEqual(spliceMachineCode(allOnes, 0,2), 7, "3 bit test");

    checkEqual(spliceMachineCode(allOnes, 1,1), 1, "1 bit shift test");
    checkEqual(spliceMachineCode(allOnes, 1,2), 3, "2 bit shift test");
    checkEqual(spliceMachineCode(allOnes, 1,3), 7, "3 bit shift test");
    checkEqual(spliceMachineCode(allOnes, 29,31), 7, "3 bit shift test @ end");

    checkEqual(spliceMachineCode(allOnes, 0,31), allOnes, "entirety test");

    int alternation = 1431677610; // 01010101010101011010101010101010
    checkEqual(spliceMachineCode(alternation, 15,16), 3, "Center test");

    // Try baseline
    MemoryStructure ms(100);
    Register r;
    Baseline b(&r, &ms);
}

