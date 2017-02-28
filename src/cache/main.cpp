#include "Cache.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

int main() {
    vector<int> *splitAddress(unsigned int address);
  {
    Cache l1Cache(5,3,2, 2, 10, NULL, NULL);
    vector<int> *result = l1Cache.splitAddress(4294967295);
    if(result->at(0) != 31 || result->at(1) != 7 || result->at(2) != 16777215) {
      cout << "FAIL:  result[0]=" << result->at(0)
           << "result[1]=" << result->at(1)
           << "result[2]=" << result->at(2) << endl;
    }
    else {
      cout << "Split address looks good so far..." << endl;
    }
    result = l1Cache.splitAddress(134217727); // put 0s in tag spot.
    if(result->at(0) != 0) {
      cout << "FAIL:  result[0]=" << result->at(0)
           << "result[1]=" << result->at(1)
           << "result[2]=" << result->at(2) << endl;
    }
    else {
      cout << "Split address looks swell!" << endl;
    }
  }
  {
    Cache l1Cache(3,3,6, 2, 10, NULL, NULL);
    Cache l2Cache(3,3,6, 2, 10, &l1Cache, NULL);
    Cache l3Cache(3,3,6, 2, 10, &l2Cache, NULL);
    l2Cache.nextCache = &l3Cache;
    l1Cache.nextCache = &l2Cache;

    l1Cache.write(22, 1234);
    CacheResult *muffins = l1Cache.read(1234);
    if(!muffins) {
      cout << "l1Cache.read returned a null!!!" << endl;
    }
    else if(muffins->at(0) != 22) {
      cout << "l1Cache.read returned " << muffins->at(0) << endl;
    }
    else {
      cout << "HAPPY 1" << endl;
    }
  }
  return 0;
}
