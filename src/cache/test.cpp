#include "Cache.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

int main() {
  {
    cout << "splitAddress tests:" << endl;
    Cache l1Cache(3, 2, 2, 10, NULL);
    vector<int> *result = l1Cache.splitAddress(1023);
    if(result->at(0) != 31 || result->at(1) != 7 || result->at(2) != 3) {
      cout << "FAIL:  result[0]=" << result->at(0)
           << "result[1]=" << result->at(1)
           << "result[2]=" << result->at(2) << endl;
    }
    else {
      cout << "PASS" << endl;
    }
    delete result;
    result = l1Cache.splitAddress(31); // put 0s in tag spot.
    if(result->at(0) != 0) {
      cout << "FAIL:  result[0]=" << result->at(0)
           << "result[1]=" << result->at(1)
           << "result[2]=" << result->at(2) << endl;
    }
    else {
      cout << "PASS" << endl;
    }
    cout << "END splitAddress tests" << endl;
    delete result;
  }
  {
    cout << "buildAddress tests:" << endl;
    Cache l1Cache(3,2, 2, 10, NULL);
    vector<int> *split = l1Cache.splitAddress(1023);
    int result = l1Cache.buildAddress(split->at(0), split->at(1), split->at(2));
    if(result == 1023) {
      cout << "PASS" << endl;
    }
    else {
      cout << "FAIL: " << result << endl;
    }
    cout << "END buildAddress tests" << endl;
    delete split;
  }
  {
    cout << "Testing addressWay..." << endl;
    Cache l1Cache(3,2, 2, 10, NULL);
    // Make sure empty at start.
    int result = l1Cache.addressWay(4294967295);
    if(result == -1) {
      cout << "PASS" << endl;
    }
    else {
      cout << "FAIL: RETURNED " << result << " on empty!" << endl;
    }
    // Still nothing is valid, even if the tag exists.
    result = l1Cache.addressWay(0);
    if(result == -1) {
      cout << "PASS" << endl;
    }
    else {
      cout << "FAIL: RETURNED " << result << " on invalid but good tag" << endl;
    }
    // Now we're valid, but bad tag.
    l1Cache.valid->at(0)->at(2) = 1;
    result = l1Cache.addressWay(4294967295);
    if(result == -1) {
      cout << "PASS" << endl;
    }
    else {
      cout << "FAIL: RETURNED " << result << " on valid but bad tag!" << endl;
    }
    // Valid and good tag should do good things.
    result = l1Cache.addressWay(0);
    if(result == 2) {
      cout << "PASS" << endl;
    }
    else {
      cout << "FAIL: RETURNED " << result << " on valid and good tag!" << endl;
    }
    cout << "END of addressWay test!" << endl;
  }
  {
    cout << "Testing updateLRU" << endl;
    Cache l1Cache(0,0, 2, 2, NULL);
    if(l1Cache.getLRUWay(0) == 0) {
      cout << "PASS" << endl;
    }
    else {
      cout << "FAIL: getLRUWay = " << l1Cache.getLRUWay(0) << endl;
    }
    l1Cache.valid->at(0)->at(0) = 1;
    l1Cache.valid->at(0)->at(1) = 1;
    l1Cache.valid->at(0)->at(2) = 1;
    l1Cache.valid->at(0)->at(3) = 1;
    for(int i = 0; i < 4; i++) {
      l1Cache.tags->at(0)->at(i) = i;
    }
    l1Cache.updateLRU(0);
    if(l1Cache.getLRUWay(0) == 1) {
      cout << "PASS" << endl;
    }
    else {
      cout << "FAIL: getLRUWay = " << l1Cache.getLRUWay(0) << endl;
    }
    l1Cache.updateLRU(1);
    l1Cache.updateLRU(2);
    if(l1Cache.getLRUWay(0) == 3) {
      cout << "PASS" << endl;
    }
    else {
      cout << "FAIL: getLRUWay = " << l1Cache.getLRUWay(0) << endl;
    }
    l1Cache.updateLRU(3);
    l1Cache.updateLRU(3);
    l1Cache.updateLRU(3);
    l1Cache.updateLRU(3);
    if(l1Cache.getLRUWay(0) == 0) {
      cout << "PASS" << endl;
    }
    else {
      cout << "FAIL: getLRUWay = " << l1Cache.getLRUWay(0) << endl;
    }
    if(l1Cache.LRU->at(0)->at(0) == 3 
     &&l1Cache.LRU->at(0)->at(1) == 2 
     &&l1Cache.LRU->at(0)->at(2) == 1 
     &&l1Cache.LRU->at(0)->at(3) == 0) {
      cout << "PASS" << endl;
    }
    else {
      cout << "FAIL:";
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
      cout << "PASS" << endl;
    }
    else {
      cout << "FAIL:";
      for(int i = 0; i < 4; i++) {
        cout << " LRU[" << i << "]=" << l1Cache.LRU->at(0)->at(i);
      }
      cout << endl;
    }
    cout << "END Testing updateLRU" << endl;
  }
  {
    cout << "Basic reading and writing test:" << endl;
    Cache l3Cache(8,0, 0, 10, NULL);
    Cache l2Cache(4,1, 2, 10, &l3Cache);
    Cache l1Cache(1,2, 2, 10, &l2Cache);
    l2Cache.nextCache = &l3Cache;
    l1Cache.nextCache = &l2Cache;

    l1Cache.write(1234, 22);
    CacheResult *muffins = l1Cache.read(22);
    if(!muffins) {
      cout << "FAIL: l1Cache.read returned a null!!!" << endl;
    }
    else if(muffins->at(0) != 1234) {
      cout << "FAIL: l1Cache.read returned " << muffins->at(0) << endl;
    }
    else {
      cout << "PASS: Can write and read single value to cache" << endl;
    }
    delete muffins;
    // Now let's see if I can read and write vectors.
    vector<int> *testVec = new vector<int>();
    for(int i = 0; i < 32; i++) {
      testVec->push_back(i);
    }
    int targAddress = 52;
    l1Cache.write(testVec, targAddress);
    delete testVec;
    muffins = l1Cache.read(targAddress, 32);
    int broke = 0;
    for(int i = 0; i < 32; i++) {
      if(muffins->at(i) != i) {
        broke = 1;
      }
    }
    if(broke) {
      cout << "FAIL: Failed with vector read/write: ";
      for(int i = 0; i < 32; i++) {
        cout << "vec[" << i << "]=" << muffins->at(i) << " ";
      }
      cout << endl;
    }
    else {
      cout << "PASS: Can write and read vector to cache" << endl;
    }
    delete muffins;
    // Now make sure vector realism safeties in place.
    testVec = new vector<int>(64, 42);
    l1Cache.write(testVec, 22);
    delete testVec;
    muffins = l1Cache.read(22, 64);
    if(muffins->size() < 64) {
      cout << "PASS: Safety cropping works!" << endl;
    }
    else {
      cout << "FAIL:  returned vec of size " << muffins->size() << endl;
    }
    delete muffins;
    // Make sure you can read through layers of cache.
    testVec = new vector<int>();
    for(int i = 0; i < 32; i++) {
      testVec->push_back(i);
    }
    targAddress = 100;
    l3Cache.write(testVec, targAddress);
    muffins = l1Cache.read(targAddress, 32);
    broke = 0;
    for(int i = 0; i < 32; i++) {
      if(muffins->at(i) != i) {
        broke = 1;
      }
    }
    if(broke) {
      cout << "FAIL: Failed to recover vector from l3: ";
      for(int i = 0; i < 32; i++) {
        cout << "vec[" << i << "]=" << muffins->at(i) << " ";
      }
      cout << endl;
    }
    else {
      cout << "PASS: Can read vector from l3" << endl;
    }
    delete muffins;
    delete testVec;
    // Now push modified versions of these values down the caches.
    vector<int> *modifiedVec = new vector<int>();
    for(int i = 0; i < 32; i++) {
      modifiedVec->push_back(i*2+1);
    }
    l1Cache.write(modifiedVec, targAddress);
#if 0
    cout << "After writing modifiedVec:" << endl;
    cout << l1Cache.toTable() << endl;
    cout << l2Cache.toTable() << endl;
    cout << l3Cache.toTable() << endl;
#endif
    testVec = new vector<int>();
    for(int i = 0; i < 32; i++) {
      testVec->push_back(i);
    }
    l1Cache.write(testVec, 0);
    delete testVec;
#if 0
    cout << "After writing testVec:" << endl;
    cout << l1Cache.toTable() << endl;
    cout << l2Cache.toTable() << endl;
    cout << l3Cache.toTable() << endl;
#endif
    // Can we recover the values we pushed down?
    muffins = l1Cache.read(targAddress, 32);
#if 0
    cout << "After reading modifiedVec:" << endl;
    cout << l1Cache.toTable() << endl;
    cout << l2Cache.toTable() << endl;
    cout << l3Cache.toTable() << endl;
#endif
    broke = 0;
    for(int i = 0; i < 32; i++) {
      if(muffins->at(i) != modifiedVec->at(i)) {
        broke = 1;
      }
    }
    if(broke) {
      cout << "FAIL: Failed to recover modified vector: ";
      for(int i = 0; i < 32; i++) {
        cout << "vec[" << i << "]=" << muffins->at(i) << " ";
      }
      cout << endl;
    }
    else {
      cout << "PASS: Can recover modified vector" << endl;
    }
    cout << "END of basic read write tests" << endl;
    delete muffins;
    delete modifiedVec;
  }
  {
    cout << "save restore tests:" << endl;
    Cache l1Cache(2,1, 1, 10, NULL);
    Cache l2Cache(2,1, 1, 10, NULL);
    vector<int> *testVec = new vector<int>();
    for(int i = 0; i < 10; i++) {
      testVec->push_back(i);
    }
    l1Cache.write(testVec, 2);
    string *state = l1Cache.save();
    l2Cache.restore(state);
    CacheResult *muffins1 = l1Cache.read(2, 16);
    CacheResult *muffins2 = l2Cache.read(2, 16);
    int broke = 0;
    for(int i = 0; i < 16; i++) {
      if(muffins1->at(i) != muffins2->at(i)) {
        broke = 1;
      }
    }
    if(broke) {
      cout << "FAIL: Failed to recover l1: ";
      for(int i = 0; i < 32; i++) {
        cout << i << muffins1->at(i) << " " << muffins2->at(i) << endl;
      }
    }
    else {
      cout << "PASS: Can recover l1" << endl;
    }
    cout << "END save restore tests" << endl;
    delete state;
    delete testVec;
    delete muffins1;
    delete muffins2;
  }
  return 0;
}
