#include "Cache.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

int main() {
  {
    cout << "splitAddress tests:" << endl;
    Cache l1Cache(5,3,2, 2, 10, NULL, NULL);
    vector<int> *result = l1Cache.splitAddress(1023);
    if(result->at(0) != 31 || result->at(1) != 7 || result->at(2) != 3) {
      cout << "FAIL:  result[0]=" << result->at(0)
           << "result[1]=" << result->at(1)
           << "result[2]=" << result->at(2) << endl;
    }
    else {
      cout << "Split address looks good so far..." << endl;
    }
    result = l1Cache.splitAddress(31); // put 0s in tag spot.
    if(result->at(0) != 0) {
      cout << "FAIL:  result[0]=" << result->at(0)
           << "result[1]=" << result->at(1)
           << "result[2]=" << result->at(2) << endl;
    }
    else {
      cout << "Split address looks swell!" << endl;
    }
    cout << "END splitAddress tests" << endl;
  }
  {
    cout << "Testing addressWay..." << endl;
    Cache l1Cache(5,3,2, 2, 10, NULL, NULL);
    // Make sure empty at start.
    int result = l1Cache.addressWay(4294967295);
    if(result == -1) {
      cout << "good so far..." << endl;
    }
    else {
      cout << "RETURNED " << result << " on empty!" << endl;
    }
    // Still nothing is valid, even if the tag exists.
    result = l1Cache.addressWay(0);
    if(result == -1) {
      cout << "good so far..." << endl;
    }
    else {
      cout << "RETURNED " << result << " on invalid but good tag" << endl;
    }
    // Now we're valid, but bad tag.
    l1Cache.valid->at(0)->at(2) = 1;
    result = l1Cache.addressWay(4294967295);
    if(result == -1) {
      cout << "good so far..." << endl;
    }
    else {
      cout << "RETURNED " << result << " on valid but bad tag!" << endl;
    }
    // Valid and good tag should do good things.
    result = l1Cache.addressWay(0);
    if(result == 2) {
      cout << "good so far..." << endl;
    }
    else {
      cout << "RETURNED " << result << " on valid and good tag!" << endl;
    }
    cout << "END of addressWay test!" << endl;
  }
  {
    cout << "Testing updateLRU" << endl;
    Cache l1Cache(5,0,0, 2, 2, NULL, NULL);
    l1Cache.valid->at(0)->at(0) = 1;
    l1Cache.valid->at(0)->at(1) = 1;
    l1Cache.valid->at(0)->at(2) = 1;
    l1Cache.valid->at(0)->at(3) = 1;
    for(int i = 0; i < 4; i++) {
      l1Cache.tags->at(0)->at(i) = i;
    }
    l1Cache.updateLRU(0);
    l1Cache.updateLRU(1);
    l1Cache.updateLRU(2);
    l1Cache.updateLRU(3);
    l1Cache.updateLRU(3);
    l1Cache.updateLRU(3);
    l1Cache.updateLRU(3);
    if(l1Cache.LRU->at(0)->at(0) == 3 
     &&l1Cache.LRU->at(0)->at(1) == 2 
     &&l1Cache.LRU->at(0)->at(2) == 1 
     &&l1Cache.LRU->at(0)->at(3) == 0) {
      cout << "Looks good." << endl;
    }
    else {
      cout << "BAD:";
      for(int i = 0; i < 4; i++) {
        cout << " LRU[" << i << "]=" << l1Cache.LRU->at(0)->at(i);
      }
      cout << endl;
    }
    l1Cache.updateLRU(0);
    l1Cache.updateLRU(0);
    l1Cache.updateLRU(0);
    if(l1Cache.LRU->at(0)->at(0) == 0 
     &&l1Cache.LRU->at(0)->at(1) == 3 
     &&l1Cache.LRU->at(0)->at(2) == 2 
     &&l1Cache.LRU->at(0)->at(3) == 1) {
      cout << "Still Looks good." << endl;
    }
    else {
      cout << "BAD:";
      for(int i = 0; i < 4; i++) {
        cout << " LRU[" << i << "]=" << l1Cache.LRU->at(0)->at(i);
      }
      cout << endl;
    }
    cout << "END Testing updateLRU" << endl;
  }
  {
    cout << "Basic reading and writing test:" << endl;
    Cache l1Cache(5,1,2, 2, 10, NULL, NULL);
    Cache l2Cache(3,4,1, 2, 10, &l1Cache, NULL);
    Cache l3Cache(0,8,0, 1, 10, &l2Cache, NULL);
    l2Cache.nextCache = &l3Cache;
    l1Cache.nextCache = &l2Cache;

    l1Cache.write(1234, 22);
    CacheResult *muffins = l1Cache.read(22);
    if(!muffins) {
      cout << "l1Cache.read returned a null!!!" << endl;
    }
    else if(muffins->at(0) != 1234) {
      cout << "l1Cache.read returned " << muffins->at(0) << endl;
    }
    else {
      cout << "Can write and read single value to cache" << endl;
    }
    cout << "END of basic reading and writing test." << endl;
  }
  return 0;
}
