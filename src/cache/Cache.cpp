#include "Cache.h"
#include <iostream>

using namespace std;

Cache::Cache( int tagBits, int indexBits, int logDataWordCount, int logAssociativity, float delay, Cache *prevCache, Cache *nextCache) {
  // Load in params.
  this->tagBits = tagBits;
  this->indexBits = indexBits;
  this->logDataWordCount = logDataWordCount;
  this->prevCache = prevCache;
  this->nextCache = nextCache;
  this->delay = delay;
  this->logAssociativity = logAssociativity;

  // Set up the cache vectors.
  tags = new vector< vector<int> * >();
  contents = new vector< vector< vector<int> * > * >();
  LRU = new vector< vector<int> * >();
  dirty = new vector< vector<int> * >();
  size_t maxIndex = 1 << indexBits;
  size_t ways = 1 << logAssociativity;
  size_t dataWordCount = 1 << logDataWordCount;
  for(size_t index = 0; index < maxIndex; index++) {
    // Add tag bits.
    tags->push_back(new vector<int>(0, ways));
    // Add content cells.
    vector< vector<int> * > *newContent = new vector<vector<int> * >();
    for(size_t way = 0; way < ways; way++) {
      newContent->push_back(new vector<int>(0, dataWordCount));
    }
    contents->push_back(newContent);
    // Add LRU bit
    LRU->push_back(new vector<int>(0, ways));
    // Add dirty bit
    dirty->push_back(new vector<int>(0, ways));
  }
  cout << "Cache done! :D" << endl;
}

CacheResult *Cache::read(unsigned int address, unsigned int length){
  vector<int> *data;
  data = new vector<int>();
  CacheResult *result = new CacheResult(*data, 42);
  return result;
}

CacheResult *Cache::read(unsigned int address){
  return read(address, 1);
}

float Cache::write(vector<int> *value, unsigned int address){
  return 42;
}

float Cache::write(int input, unsigned int address){
  vector<int> *vectorInput = new vector<int>(input);
  write(vectorInput, address);
  return 42;
}

string *Cache::save(){
  string *result = new string("42");
  return result;
}

void Cache::restore(string *xml){
}


