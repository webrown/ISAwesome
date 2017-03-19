#include "Cache.h"
#include <stdlib.h>
#include <iostream>
#include "MainMemory.h"
#include "Register.h"

using namespace std;

int main() {
  {
    cout << "splitAddress tests:" << endl;
    Cache l1Cache(3, 2, 2, 10, NULL);
    QVector<int> *result = l1Cache.splitAddress(1023);
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
    QVector<int> *split = l1Cache.splitAddress(1023);
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
    (*l1Cache.valid->at(0))[2] = 1;
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
    (*l1Cache.valid->at(0))[0] = 1;
    (*l1Cache.valid->at(0))[1] = 1;
    (*l1Cache.valid->at(0))[2] = 1;
    (*l1Cache.valid->at(0))[3] = 1;
    for(int i = 0; i < 4; i++) {
      (*l1Cache.tags->at(0))[i] = i;
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
    QueryResult *muffins = l1Cache.read(22);
    if(!muffins) {
      cout << "FAIL: l1Cache.read returned a null!!!" << endl;
    }
    else if(muffins->at(0).i != 1234) {
      cout << "FAIL: l1Cache.read returned " << muffins->at(0).i << endl;
    }
    else {
      cout << "PASS: Can write and read single value to cache" << endl;
    }
    delete muffins;
    // Now let's see if I can read and write vectors.
    QVector<int> *testVec = new QVector<int>();
    for(int i = 0; i < 32; i++) {
      testVec->push_back(i);
    }
    int targAddress = 52;
    l1Cache.write(testVec, targAddress);
    delete testVec;
    muffins = l1Cache.read(targAddress, 32);
    int broke = 0;
    for(int i = 0; i < 32; i++) {
      if(muffins->at(i).i != i) {
        broke = 1;
      }
    }
    if(broke) {
      cout << "FAIL: Failed with vector read/write: ";
      for(int i = 0; i < 32; i++) {
        cout << "vec[" << i << "]=" << muffins->at(i).i << " ";
      }
      cout << endl;
    }
    else {
      cout << "PASS: Can write and read vector to cache" << endl;
    }
    delete muffins;
    // Now make sure vector realism safeties in place.
    testVec = new QVector<int>(64, 42);
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
    testVec = new QVector<int>();
    for(int i = 0; i < 32; i++) {
      testVec->push_back(i);
    }
    targAddress = 100;
    l3Cache.write(testVec, targAddress);
    muffins = l1Cache.read(targAddress, 32);
    broke = 0;
    for(int i = 0; i < 32; i++) {
      if(muffins->at(i).i != i) {
        broke = 1;
      }
    }
    if(broke) {
      cout << "FAIL: Failed to recover vector from l3: ";
      for(int i = 0; i < 32; i++) {
        cout << "vec[" << i << "]=" << muffins->at(i).i << " ";
      }
      cout << endl;
    }
    else {
      cout << "PASS: Can read vector from l3" << endl;
    }
    delete muffins;
    delete testVec;
    // Now push modified versions of these values down the caches.
    QVector<int> *modifiedVec = new QVector<int>();
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
    testVec = new QVector<int>();
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
      if(muffins->at(i).i != modifiedVec->at(i)) {
        broke = 1;
      }
    }
    if(broke) {
      cout << "FAIL: Failed to recover modified vector: ";
      for(int i = 0; i < 32; i++) {
        cout << "vec[" << i << "]=" << muffins->at(i).i << " ";
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
    QVector<int> *testVec = new QVector<int>();
    for(int i = 0; i < 10; i++) {
      testVec->push_back(i);
    }
    l1Cache.write(testVec, 2);
    l1Cache.write(-42, 19);
    QString *state = l1Cache.save();
    l2Cache.restore(state);
    QueryResult *muffins1 = l1Cache.read(2, 16);
    QueryResult *muffins2 = l2Cache.read(2, 16);
    int broke = 0;
    for(int i = 0; i < 16; i++) {
      if(muffins1->at(i).i != muffins2->at(i).i) {
        broke = 1;
      }
    }
    if(broke) {
      cout << "FAIL: Failed to recover l1: " << endl;
      cout << l1Cache.toTable().toUtf8().constData() << endl;
      cout << l2Cache.toTable().toUtf8().constData() << endl;
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
  {
    // Just a minor sanity test, make sure we don't barf when we do floats.
    cout << "BEGIN:  Test floats" << endl;
    float original = 101.01;
    Cache l2Cache(2,1, 1, 10, NULL);
    Cache l1Cache(10,0, 0, 10, &l2Cache);
    for(int address = 0; address < 1000; address++) {
      l1Cache.write(original, address);
      original = original + 1.0;
    }
    QVector<Value> heard;
    bool broke = false;
    original = 101.01;
    for(int address = 0; address < 1000; address++) {
      QueryResult *qr = l1Cache.read(address);
      heard.push_back(qr->result.at(0));
      delete qr;
      if(heard.back().f != original) broke = true;
      original = original + 1.0;
    }
    if(broke) {
      cout << "FAILED:  Stored floats do not match." << endl;
      for(int i = 0; i < heard.size(); i++) {
        cout << heard.at(i).f << endl;
      }
    }
    else {
      cout << "PASS:  Floats could be written/read." << endl;
    }
    cout << "END:  Test floats" << endl;
  }
  {
    cout << "BEGIN: MainMemory tests." << endl;
    MainMemory m(100);
    QueryResult *result = NULL;
    result = m.read(100);
    if(result->result.size() == 1) {
      cout << "PASS:  Single read when empty gave single result." << endl;
    }
    else {
      cout << "FAIL:  Single read when empty gave vector of size " << result->result.size() << "." << endl;
    }
    if(result->result.at(0).i == 0) {
      cout << "PASS:  Single read when empty gave zero result." << endl;
    }
    else {
      cout << "FAIL:  Single read when empty gave " << result->result.at(0).i << "." << endl;
      for(int i = 0; i < result->result.size(); i++) cout << result->result.at(i).i << endl;
    }
    delete result;

    result = m.read(2, 64);
    if(result->result.size() == 64) {
      cout << "PASS:  64 read when empty gave 64 results." << endl;
    }
    else {
      cout << "FAIL:  64 read when empty gave vector of size " << result->result.size() << "." << endl;
    }
    if(result->result.at(63).i == 0) {
      cout << "PASS:  64 read when empty gave zero result." << endl;
    }
    else {
      cout << "FAIL:  64 read when empty gave " << result->result.at(63).i << "." << endl;
      for(int i = 0; i < result->result.size(); i++) cout << result->result.at(i).i << endl;
    }
    delete result;

    result = m.read(MainMemory::MEMORY_CHUNK_SIZE-3, 64);
    if(result->result.size() == 64) {
      cout << "PASS:  64 boundary read when empty gave 64 results." << endl;
    }
    else {
      cout << "FAIL:  64 boundary read when empty gave vector of size " << result->result.size() << "." << endl;
    }
    if(result->result.at(63).i == 0) {
      cout << "PASS:  64 boundary read when empty gave zero result." << endl;
    }
    else {
      cout << "FAIL:  64 boundary read when empty gave " << result->result.at(63).i << "." << endl;
      for(int i = 0; i < result->result.size(); i++) cout << result->result.at(i).i << endl;
    }
    delete result;

    m.write(42, 100);
    result = m.read(100);
    if(result->result.size() == 1) {
      cout << "PASS:  Single read with contents gave single result." << endl;
    }
    else {
      cout << "FAIL:  Single read with contents gave vector of size " << result->result.size() << "." << endl;
    }
    if(result->result.at(0).i == 42) {
      cout << "PASS:  Single read with contents gave right result." << endl;
    }
    else {
      cout << "FAIL:  Single read with contents gave " << result->result.at(0).i << ", not 42." << endl;
      for(int i = 0; i < result->result.size(); i++) cout << result->result.at(i).i << endl;
    }
    delete result;

    m.write(42, 3);
    result = m.read(2, 64);
    if(result->result.size() == 64) {
      cout << "PASS:  64 read with contents gave 64 results." << endl;
    }
    else {
      cout << "FAIL:  64 read with contents gave vector of size " << result->result.size() << "." << endl;
    }
    if(result->result.at(1).i == 42) {
      cout << "PASS:  64 read with contents gave correct result." << endl;
    }
    else {
      cout << "FAIL:  64 read with contents gave " << result->result.at(63).i << ", not 42." << endl;
      for(int i = 0; i < result->result.size(); i++) cout << result->result.at(i).i << endl;
    }
    delete result;

    m.write(42, MainMemory::MEMORY_CHUNK_SIZE-3);
    m.write(42, MainMemory::MEMORY_CHUNK_SIZE-1);
    m.write(42, MainMemory::MEMORY_CHUNK_SIZE+3);
    result = m.read(MainMemory::MEMORY_CHUNK_SIZE-3, 64);
    if(result->result.size() == 64) {
      cout << "PASS:  64 boundary read with contents gave 64 results." << endl;
    }
    else {
      cout << "FAIL:  64 boundary read with contents gave vector of size " << result->result.size() << "." << endl;
    }
    if(result->result.at(0).i == 42 && result->result.at(2).i == 42 && result->result.at(6).i == 42) {
      cout << "PASS:  64 boundary read with contents gave right results." << endl;
    }
    else {
      cout << "FAIL:  64 boundary read with contents gave " << result->result.at(0).i << " and " << result->result.at(2).i << " and " << result->result.at(6).i << "." << endl;
      for(int i = 0; i < result->result.size(); i++) cout << result->result.at(i).i << endl;
    }
    delete result;

    MainMemory m2(100);
    m2.write(1000, 1000);
    QString *state = m.save();
    m2.restore(state);
    delete state;
    bool broke = false;
    for(int i = 0; i < m2._contents.size(); i++) {
        for(int j = 0; j < m2._contents.at(i).size(); j++) {
            if(m._contents.at(i).at(j).toInt != m2._contents.at(i).at(j).toInt) {
                broke = true;
            }
        }
    }
    if(broke) {
        cout << "FAIL: save/restore broke things." << endl;
    }
    else {
        cout << "PASS: save/restore worked." << endl;
    }

    cout << "END: MainMemory tests." << endl;
  }
  {
    cout << "BEGIN:  Register tests." << endl;
    Register r;
    r.write(42, 10);
    QueryResult *qr = r.read(10);
    if(qr->result.at(0).i == 42) {
      cout << "PASS:  Can write/read a single integer scalar value." << endl;
    }
    else {
      cout << "FAIL:  Cannot write/read a single integer scalar value." << qr->result.at(0).i << endl;
    }
    delete qr;

    for(int i = 0; i < 24; i++) {
        Value v;
        v.f = i;
        r.write(v,i);
    }
    for(int i = 0; i < 24; i++) {
        QueryResult *qr = r.read(i);
        if(qr->result.at(0).f == i) {
          cout << "PASS:  Can write/read to address " << i << endl;
        }
        else {
          cout << "FAIL:  Cannot write/read to address " << i << endl;
        }
        delete qr;
    }
cout << "A" << endl;

    Value counter = {0};
    for(int i = 24; i < 33; i++) {
        QVector<Value> vec;
        for(int j = 0; j < 64; j++) {
            vec.push_back(counter);
            counter.i++;
        }
cout << "i=" << counter.i << endl;
        r.write(&vec,i);
    }
cout << "B" << endl;
    counter.i = 0;
    for(unsigned int i = 24; i < 33; i++) {
        QueryResult *qr = r.read(i, 64);
        for(int j = 0; j < 64; j++) {
            if(qr->result.at(j).i == counter.i) {
              cout << "PASS:  Can write/read to vector word " << counter.i << "." << endl;
            }
            else {
              cout << "FAIL:  Cannot write/read to vector word " << counter.i << "." << qr->result.at(j).i << endl;
            }
            counter.i++;
        }
        delete qr;
    }

    // Just make sure we can do this syntax...
    r.write(-1, 0);
    r.read(Register::PC);
    r.read(Register::scalarFloats+3);

    // Save/restore
    Register r2;
    QString *state = r.save();
    r2.restore(state);
    delete state;
    for(int i = 0; i < 24; i++) {
        QueryResult *qr1 = r.read(i);
        QueryResult *qr2 = r2.read(i);
        if(qr1->result.at(0).i == qr2->result.at(0).i) {
            cout << "PASS:  saved and restored " << qr1->result.at(0).i << " " << qr2->result.at(0).i << endl;
        }
        else {
            cout << "FAIL:  cannot save and restore " << qr1->result.at(0).i << " " << qr2->result.at(0).i << endl;
        }
    }
    for(int i = 24; i < 33; i++) {
        QueryResult *qr1 = r.read(i, 64);
        QueryResult *qr2 = r2.read(i, 64);
        for(int j = 0; j < 64; j++) {
            if(qr1->result.at(j).i == qr2->result.at(j).i) {
                cout << "PASS:  saved and restored " << qr1->result.at(j).i << " " << qr2->result.at(j).i << endl;
            }
            else {
                cout << "FAIL:  cannot save and restore " << qr1->result.at(j).i << " " << qr2->result.at(j).i << endl;
            }
        }
    }

    cout << "END:  Register tests." << endl;
  }
  return 0;
}
