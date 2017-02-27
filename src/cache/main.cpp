#include "Cache.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

int main() {
  {
    Cache l1Cache(3,5,6, 2, 10, NULL, NULL);
    Cache l2Cache(3,5,6, 2, 10, &l1Cache, NULL);
    Cache l3Cache(3,5,6, 2, 10, &l2Cache, NULL);
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
