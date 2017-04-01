// This is a program to map out assembly program.
#include <vector>
#include <iostream>

using namespace std;

void getMatrixDims(vector<int> *matrix, int *r, int *c) {
  *r = (*matrix)[0];
  *c = (*matrix)[1];
}

void initMatrix(vector<int> *matrix, int r, int c) {
  matrix->resize(2+r*c);
  (*matrix)[0] = r;
  (*matrix)[1] = c;
}

void matrixGetVal(vector<int> *matrix, int r, int c, int *result) {
  int mr;
  int mc;
  getMatrixDims(matrix, &mr, &mc);;

  int index;
  index = 2;
  index += r*mc;
  index += c;

  *result = matrix->at(index);
}

void matrixMult(vector<int> *matrix1, vector<int> *matrix2, vector<int> *result){
  // Check if dimensions match.
  int m1r;
  int m1c;
  int m2r;
  int m2c;
  getMatrixDims(matrix1, &m1r, &m1c);
  getMatrixDims(matrix2, &m2r, &m2c);
  if(m1c != m2r) {
    // Matrix dims don't match.  Barf.
    initMatrix(result, 0, 0);
    return;
  }
  // Matrix dims healthy, carry on!
  initMatrix(result, m1r, m2c);

  int writeTo = 2;
  int result_row;
  int result_column;
  int sum;
  int innerStrobe;
  int prod;
  int mult1;
  int mult2;
  for(result_row = 0; result_row < m1r; result_row++) {
    // For every row...
    for(result_column = 0; result_column < m2c; result_column++) {
      // For every column, take a sum.
      sum = 0;
      for(innerStrobe = 0; innerStrobe < m1c; innerStrobe++) {
        matrixGetVal(matrix1, result_row, innerStrobe, &mult1);
        matrixGetVal(matrix2, innerStrobe, result_column, &mult2);
        prod = mult1 * mult2;
        sum += prod;
      }
      // Record
      (*result)[writeTo] = sum;
      writeTo++;
    }
  }
}

int main() {
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
  // Check result
  for(int i = 0; i < result.size(); i++) {
    cout << result.at(i);
    if(expected.at(i) != result.at(i)) {
      cout << " FAIL!!!!!!!!!!!!!!!!!!! " << expected.at(i);
    }
    cout << endl;
  }
}


