// This is a program to map out assembly program.
#include <vector>
#include <iostream>

using namespace std;

//NOT 0 SP ; Start stack pointer far away
//BL MAIN

void getMatrixDims(vector<int> *matrix, int *r, int *c) {
  // R0 = matrixAddr
  // R1 = r
  // R2 = c
  *r = (*matrix)[0];
//STO R0 R1
  *c = (*matrix)[1];
//CPY R0 R2
//ADD  1 R2
//STO R2 R2
}

void initMatrix(vector<int> *matrix, int r, int c) {
  // R0 = matrixAddr
  // R1 = r
  // R2 = c
  matrix->resize(2+r*c);
  (*matrix)[0] = r;
//STO R0 R1
//ADD  1 R0
  (*matrix)[1] = c;
//STO R0 R2
//ADD  1 R0
}

void matrixGetVal(vector<int> *matrix, int r, int c, int *result) {
  // R0 = matrixAddr
  // R1 = r           AT START, BUT QUICKLY BECOMES mr
  // R2 = c           AT START, BUT QUICKLY BECOMES mc, then r*mc
  // R3 = result
  // R4 = GENERAL SPARE
  // R5 = r longterm
  // R6 = c longterm
//CPY R1 R5
//CPY R2 R6
  int mr;
  int mc;
  getMatrixDims(matrix, &mr, &mc);;
//CPY GETMATRIXDIMS R4
//BL R4
  *result = 2;
//CPY 2 R3
  mc *= r;
//MUL R5 R2
  *result += mc;
//ADD R2 R3
  *result += c;
//ADD R6 R3
  *result = matrix->at(*result);
//LOD R3 R3
}

void matrixMult(vector<int> *matrix1, vector<int> *matrix2, vector<int> *result){
  // R0 = matrix1Addr
  // R1 = matrix2Addr
  // R2 = resultAddr+writeTo
  // R3 = GENERAL SPARE
  // R4 = m1r
  // R5 = mmatching
  // R6 = innerStrobe
  // R7 = m2c
  // R8 = result_row
  // R9 = result_column;
  // R10 = sum;
  // R11 = mult1;
  // R12 = mult2;
  // R13 = extra matrix1Addr
  // R14 = extra matrix2Addr
  // R15 = extra result

  // Check if dimensions match.
  int m1r;
  int mmatching;
  int innerStrobe; // Just being used early for recycling's sake
  int m2c;

  getMatrixDims(matrix1, &m1r, &mmatching);
//CPY R0 R13; save matrix1Addr away in an arbitrary space.
//CPY R1 R14; save matrix2Addr away in an arbitrary space.
//CPY R2 R15; save result away in an arbitrary space.
//CPY GETMATRIXDIMS R3
//BL R3
//CPY R1 R4
//CPY R2 R5
  getMatrixDims(matrix2, &innerStrobe, &m2c);
//CPY R14 R0
//BL R3
//CPY R1 R6
//CPY R2 R7
  if(mmatching != innerStrobe) {
//CMP R5 R6
    // Matrix dims don't match.  Barf.
    initMatrix(result, 0, 0);
    return;
  }
  // Matrix dims healthy, carry on!
  initMatrix(result, m1r, m2c);
//CPY R15 R0 ; Place result (both cases).
//NE CPY 0 R1 
//EQ CPY R4 R1 
//NE CPY 0 R2 
//EQ CPY R7 R2 
//BL R3 ; Call initMatrix
//NE BL LR ; return if mismatch

//;Move R0-R2 back in place.  Make R chart correct again.
//CPY R13 R0
//CPY R14 R1
//CPY R15 R2

  int writeTo = 2;
  int result_row;
  int result_column;
  int sum;
  int mult1;
  int mult2;
//CPY 0 R8
  for(result_row = 0; result_row < m1r; result_row++) {
//OUTERLOOP:
    // For every row...
    for(result_column = 0; result_column < m2c; result_column++) {
//MIDDLELOOP:
      // For every column, take a sum.
      sum = 0;
//CPY  0  R3
//TOF R3 R10 ; Storing stuff in Floats to save space.
      for(innerStrobe = 0; innerStrobe < mmatching; innerStrobe++) {
//INNERLOOP:
        matrixGetVal(matrix1, result_row, innerStrobe, &mult1);
//CPY R8 R1
//CPY R2 R15 ; Hide resultAddr
//CPY R6 R2
//CPY MATRIXGETVAL R4
//BL R4
//TOF R3 R11 ; Store result in mult1
        matrixGetVal(matrix2, innerStrobe, result_column, &mult2);
//CPY R14 R0
//CPY R6 R1
//CPY R9 R2
//BL R4
//TOF R3 R12 ; Store result in mult1
//CPY R15 R2 ; Bring back resultAddr
        mult2 *= mult1;
//MUL R11 R12
        sum += mult2;
//ADD R12 R10
      }
//ADD  1 R6
//CMP R6 R5
//LT B INNERLOOP
      // Record
      (*result)[writeTo] = sum;
//TOI R10 R3
//STO R2 R3
      writeTo++;
//ADD 1 R2
    }
//ADD  1 R9
//CMP R9 R7
//LT B MIDDLELOOP
  }
//ADD  1 R8
//CMP R8 R4
//LT B OUTERLOOP
}

int main() {
  // R0 = matrix1
  // R1 = matrix2
  // R2 = result
  // R4 = GENERAL SPARE
  // Set up example
  vector<int> matrix1;
  matrix1.push_back(2);
  matrix1.push_back(3);
  matrix1.push_back(1);
  matrix1.push_back(2);
  matrix1.push_back(3);
  matrix1.push_back(4);
  matrix1.push_back(5);
  matrix1.push_back(6);

  vector<int> matrix2;
  matrix2.push_back(3);
  matrix2.push_back(4);
  matrix2.push_back(1);
  matrix2.push_back(2);
  matrix2.push_back(3);
  matrix2.push_back(4);
  matrix2.push_back(5);
  matrix2.push_back(6);
  matrix2.push_back(7);
  matrix2.push_back(8);
  matrix2.push_back(9);
  matrix2.push_back(10);
  matrix2.push_back(11);
  matrix2.push_back(12);

  vector<int> expected;
  expected.push_back(2);
  expected.push_back(4);
  expected.push_back(38);
  expected.push_back(44);
  expected.push_back(50);
  expected.push_back(56);
  expected.push_back(83);
  expected.push_back(98);
  expected.push_back(113);
  expected.push_back(128);

  vector<int> result;

  matrixMult(&matrix1, &matrix2, &result);
//CPY MATRIXMULT R4 
//BL R4 
  // Check result
  for(unsigned int i = 0; i < result.size(); i++) {
    cout << result.at(i);
    if(expected.at(i) != result.at(i)) {
      cout << " FAIL!!!!!!!!!!!!!!!!!!! " << expected.at(i);
    }
    cout << endl;
  }
}


