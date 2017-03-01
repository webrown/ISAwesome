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
  valid = new vector< vector<int> * >();
  size_t maxIndex = 1 << indexBits;
  size_t ways = 1 << logAssociativity;
  size_t dataWordCount = 1 << logDataWordCount;
  for(size_t index = 0; index < maxIndex; index++) {
    // Add tag bits.
    tags->push_back(new vector<int>(ways, 0));
    // Add content cells.
    vector< vector<int> * > *newContent = new vector<vector<int> * >();
    for(size_t way = 0; way < ways; way++) {
      newContent->push_back(new vector<int>(dataWordCount, 0));
    }
    contents->push_back(newContent);
    // Add LRU bit
    LRU->push_back(new vector<int>(ways, 0));
    // Add dirty bit
    dirty->push_back(new vector<int>(ways, 0));
    // Add valid bit
    valid->push_back(new vector<int>(ways, 0));
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

int Cache::addressWay(unsigned int address){
  // Returns the associative way that a certain address is at.
  // If there is no way, return -1.
  vector<int> tagIndOff = * splitAddress(address);
  for(int i = 0; i < tags->at(tagIndOff[1])->size(); i++) {
    if(!valid->at(tagIndOff[1])->at(i)) {
      // If valid bit is not set, this is not a valid cell to think about.
      continue;
    }
    if(tags->at(tagIndOff[1])->at(i) == tagIndOff[0]) {
      // Aha!  The tag matches!  This is your way!
      return i;
    }
  }
  // Saw nothing!
  return -1;
}

float Cache::write(int input, unsigned int address){
  // No matter what, you will need to wait your delay.
  float wait = delay;
  // Is the value you want in the cache? TODO
  int way = addressWay(address);
  if(way == -1) {
    // If not, pull in the value.
    
  }
  // Write to the specified index.
  vector<int> tagIndOff = * splitAddress(address);
  contents->at(tagIndOff.at(1))->at(way)->at(tagIndOff.at(2)) = input;
  
  // Tell the layer above how long this took.
  return delay;
}

string *Cache::save(){
  string *result = new string("42");
  return result;
}

void Cache::restore(string *xml){
}


vector<int> *Cache::splitAddress(unsigned int address){
  // Returns three-long vector:
  // [0] - tag
  // [1] - index
  // [2] - offset
  vector<int> *result = new vector<int>();
  result->push_back(address >> (indexBits + logDataWordCount));
  result->push_back((address >> (logDataWordCount)) % (1 << indexBits));
  result->push_back(address % (1 << (logDataWordCount)));
  return result;
}
