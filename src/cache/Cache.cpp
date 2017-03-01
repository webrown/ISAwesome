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
}

CacheResult *Cache::read(unsigned int address, unsigned int length){
  float wait = delay;
  // Is value present?
  int way = addressWay(address);
  // TODO If not, grab it
  vector<int> tagIndOff = * splitAddress(address);
  if(way == -1) {
    way = 0; // TODO REMOVE THIS LATER
    tags->at(tagIndOff[1])->at(way) = tagIndOff[0];
  }
  // TODO Read value.
  vector<int> *data;
  data = new vector<int>(1,contents->at(tagIndOff.at(1))->at(way)->at(tagIndOff.at(2)));
  CacheResult *result = new CacheResult(*data, wait);
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
  // Is the value you want in the cache?
  vector<int> tagIndOff = * splitAddress(address);
  int way = addressWay(address);
  if(way == -1) {
    // If not, remove LRU value and pull in new value. TODO
    way = 0; // TODO THIS IS WRONG
    tags->at(tagIndOff[1])->at(way) = tagIndOff[0];
  }
  // Write to the specified index.
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

unsigned int Cache::firstInLine(unsigned int address) {
  // Returns the line first address on the line of a given address.
  int dataPerLine = contents->at(0)->at(0)->size();
  return address - (address % dataPerLine);
}

void Cache::updateLRU(unsigned int address){
  // Call this to bring an address to the front of its LRU queue.
  // Can you find this address?
  int way = addressWay(address);
  if(way == -1) {
    return;
  }
  vector<int> tagIndOff = * splitAddress(address);
  // What is your current spot in the queue?
  int queuePosition = LRU->at(tagIndOff[1])->at(way);
  // Anyone in font of you just got cut.
  for(int i = 0; i < LRU->at(0)->size(); i++) {
    if(LRU->at(tagIndOff[1])->at(i) <= queuePosition) {
      LRU->at(tagIndOff[1])->at(i)++;
    }
  }
  // Move to the front of the queue.
  LRU->at(tagIndOff[1])->at(way) = 0;
}

float Cache::fetch(unsigned int address){
  // Pull this value into the cache from the caches below.
  // Returns the amount of time it took to fetch this.

  // Maybe you already have the item!
  int way = addressWay(address);
  if(way != -1) {
    // We don't need to do anything!
    return 0;
  }
  float wait = 0;
  vector<int> tagIndOff = * splitAddress(address);
  // At this point, an eviction is needed.
  // TODO Find the item with the worst LRU
  // What is the first address this involves?
  int firstEvictedAddress = firstInLine(0); // TODO needs to change.
  // Write to the cache below if dirty and able.
  if(dirty->at(tagIndOff[1])->at(way) && nextCache) {
    wait += nextCache->write(firstEvictedAddress, contents->at(0)->at(0)->size());
  }
  // Set tag and valid bits
  tags->at(tagIndOff[1])->at(way) = tagIndOff[0];
  valid->at(tagIndOff[1])->at(way) = 1;
  // Get value from below.
  if(nextCache) {
    CacheResult *resultFromBelow = nextCache->read(firstInLine(address), contents->at(0)->at(0)->size());
    for(int i = 0; i < contents->at(0)->at(0)->size(); i++) {
      contents->at(tagIndOff[1])->at(way)->at(i) = resultFromBelow->result.at(i);
    }
    wait += resultFromBelow->time;
  }
  return wait;
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
