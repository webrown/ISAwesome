#include "AndOperation.h"
Value AndOperation::scalarOperation(int a, int b){
  Value v;
  v.i = a & b;
  return v;
}
