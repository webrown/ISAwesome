#include "Cache.h"
#include <iostream>
#include <algorithm>
#include <sstream>

using namespace std;

Cache::Cache(int indexBits, int logDataWordCount, int logAssociativity, double delay, Cache *nextCache) {
  // Load in params.
  this->indexBits = indexBits;
  this->logDataWordCount = logDataWordCount;
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

Cache::~Cache() {
  // Clean tags
  for(int i = 0; i < tags->size(); i++) {
    delete tags->at(i);
  }
  delete tags;
  // Clean contents
  for(int i = 0; i < contents->size(); i++) {
    for(int j = 0; j < contents->at(i)->size(); j++) {
      delete contents->at(i)->at(j);
    }
    delete contents->at(i);
  }
  delete contents;
  // Clean LRUs
  for(int i = 0; i < LRU->size(); i++) {
    delete LRU->at(i);
  }
  delete LRU;
  // Clean dirty
  for(int i = 0; i < dirty->size(); i++) {
    delete dirty->at(i);
  }
  delete dirty;
  // Clean valid
  for(int i = 0; i < valid->size(); i++) {
    delete valid->at(i);
  }
  delete valid;
}

unsigned int Cache::buildAddress(unsigned int tag, unsigned int index, unsigned int offset){
  // Concatenate tag, index, and offset into an address.
  return (tag << (indexBits + logDataWordCount)) | (index << logDataWordCount) | offset;
}

CacheResult *Cache::read(unsigned int address, unsigned int length){
  // Hardware constraint:  Can't parallel load more values than there are in the cache.
  int mL = maxLength(address);
  if(length > mL) {
    length = mL;
    cout << "WARNING:  read given too large a vector, shrinking size to " << mL << "." << endl;
  }
  double wait = delay;
  // Get these values into the cache if they are not already.
  double fetchWait = 0;
  vector<int> *data = new vector<int>();
  for(int i = address; i < address+length; i++) {
    // TODO May be able to be optimized later; often tag and index won't change for long periods of time.
    fetchWait = max(fetchWait, fetch(i));
    // Now at front of LRU queue
    updateLRU(i);
    // Read value.
    int way = addressWay(i);
    vector<int> *tagIndOff = splitAddress(i);
    int index = tagIndOff->at(1);
    int offset = tagIndOff->at(2);
    delete tagIndOff;
    data->push_back(contents->at(index)->at(way)->at(offset));
  }
  // All fetches happened in parallel.
  wait += fetchWait;
  CacheResult *result = new CacheResult(*data, wait);
  delete data;
  return result;
}

CacheResult *Cache::read(unsigned int address){
  return read(address, 1);
}

size_t Cache::maxLength(unsigned int startAddress){
  // Return the maximum length off of this address you can fit in cache.
  // Get the size of the cache.
  size_t result =  contents->size() * contents->at(0)->size() * contents->at(0)->at(0)->size();
  // How many slots will get wasted due to the startAddress not taking a complete line?
  result -= startAddress % contents->at(0)->at(0)->size();
  return result;
}

double Cache::write(vector<int> *value, unsigned int address){
  int mL = maxLength(address);
  int mustDeleteValue = 0;
  if(value->size() > mL) {
    value = new vector<int>(value->begin(), value->begin()+mL);
    // You'll have to clean up this new vector later!
    mustDeleteValue = 1;
    cout << "WARNING:  write given too large a vector, shrinking size to " << mL << "." << endl;
  }
#if 0
  cout << "Cache::write value = ";
  for(int i = 0; i < value->size(); i++) {
    cout << value->at(i) << " ";
  }
  cout << endl;
#endif
  // No matter what, you will need to wait your delay.
  double wait = delay;
  // Get the value you want into cache.
  double fetchWait = 0;
  for(int i = 0; i < value->size(); i++) {
    fetchWait = max(fetchWait, fetch(address+i));
    cout << "FW:" << fetchWait << endl;
    // Move up in LRU queue.
    updateLRU(address+i);
    // If this is going to change the value, the value is becoming dirty.
    vector<int> *tagIndOff = splitAddress(address+i);
    int index = tagIndOff->at(1);
    int offset = tagIndOff->at(2);
    delete tagIndOff;
    int way = addressWay(address+i);
    if(contents->at(index)->at(way)->at(offset) != value->at(i)) {
      dirty->at(index)->at(way) = 1;
      // Write to the specified index.
      contents->at(index)->at(way)->at(offset) = value->at(i);
    }
  }
  wait += fetchWait;
  if(mustDeleteValue) {
    delete value;
  }
  // Tell the layer above how long this took.
  return wait;
}

int Cache::addressWay(unsigned int address){
  // Returns the associative way that a certain address is at.
  // If there is no way, return -1.
  vector<int> *tagIndOff = splitAddress(address);
  int tag = tagIndOff->at(0);
  int index = tagIndOff->at(1);
  delete tagIndOff;
  for(int i = 0; i < tags->at(index)->size(); i++) {
    if(!valid->at(index)->at(i)) {
      // If valid bit is not set, this is not a valid cell to think about.
      continue;
    }
    if(tags->at(index)->at(i) == tag) {
      // Aha!  The tag matches!  This is your way!
      return i;
    }
  }
  // Saw nothing!
  return -1;
}

double Cache::write(int input, unsigned int address){
  vector<int> *tinyVector = new vector<int>(1, input);
  double result = write(tinyVector, address);
  delete tinyVector;
  return result;
}

string *Cache::save(){
  string *result = new string();
  for(int ind = 0; ind < contents->size(); ind++) {
    for(int way = 0; way < contents->at(0)->size(); way++) {
      // Record contents
      for(int offset = 0; offset < contents->at(0)->at(0)->size(); offset++) {
        *result += contents->at(ind)->at(way)->at(offset);
      }
      // Record dirty
      *result += dirty->at(ind)->at(way);
      // Record LRU
      *result += LRU->at(ind)->at(way);
      // Record tag
      *result += tags->at(ind)->at(way);
      // Record valid
      *result += valid->at(ind)->at(way);
    }
  }
  return result;
}

void Cache::restore(string *state){
  if(!state) {
    return;
  }
  int stateIndex = 0;
  for(int ind = 0; ind < contents->size(); ind++) {
    for(int way = 0; way < contents->at(0)->size(); way++) {
      // Place contents.
      for(int offset = 0; offset < contents->at(0)->at(0)->size(); offset++) {
        if(stateIndex == state->size()) {
          return;
        }
        contents->at(ind)->at(way)->at(offset) = state->at(stateIndex++);
      }
      // Place in dirty.
      if(stateIndex == state->size()) {
        return;
      }
      dirty->at(ind)->at(way) = state->at(stateIndex++);
      // Place in LRU.
      if(stateIndex == state->size()) {
        return;
      }
      LRU->at(ind)->at(way) = state->at(stateIndex++);
      // Place in tag.
      if(stateIndex == state->size()) {
        return;
      }
      tags->at(ind)->at(way) = state->at(stateIndex++);
      // Place in valid.
      if(stateIndex == state->size()) {
        return;
      }
      valid->at(ind)->at(way) = state->at(stateIndex++);
    }
  }
}

unsigned int Cache::getLRUWay(unsigned int index){
  // Returns the index that is least recently used.
  int LRUWay = 0;
  for(int i = 0; i < LRU->at(0)->size(); i++) {
    if(LRU->at(index)->at(i) > LRU->at(index)->at(LRUWay)) {
      LRUWay = i;
    }
  }
  return LRUWay;
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
  vector<int> *tagIndOff = splitAddress(address);
  int index = tagIndOff->at(1);
  delete tagIndOff;
  // What is your current spot in the queue?
  int queuePosition = LRU->at(index)->at(way);
  // Anyone in font of you just got cut.
  for(int i = 0; i < LRU->at(0)->size(); i++) {
    if(LRU->at(index)->at(i) <= queuePosition) {
      LRU->at(index)->at(i)++;
    }
  }
  // Move to the front of the queue.
  LRU->at(index)->at(way) = 0;
}

double Cache::fetch(unsigned int address){
  // Pull this value into the cache from the caches below.
  // Returns the amount of time it took to fetch this.

  // Maybe you already have the item!
  int way = addressWay(address);
  if(way != -1) {
    // We don't need to do anything!
    return 0;
  }
  double wait = 0;
  vector<int> *tagIndOff = splitAddress(address);
  int index = tagIndOff->at(1);
  int tag = tagIndOff->at(0);
  delete tagIndOff;
  // At this point, an eviction is needed.
  // Find the item with the worst LRU
  way = getLRUWay(index);
  // What is the first address on the evicted line?
  int firstEvictedAddress = buildAddress(tags->at(index)->at(way), index, 0);
  // Write to the cache below if dirty and able.
  if(dirty->at(index)->at(way) && nextCache) {
    wait += nextCache->write(contents->at(index)->at(way), firstEvictedAddress);
  }
  // Set tag and valid bits
  tags->at(index)->at(way) = tag;
  valid->at(index)->at(way) = 1;
  // Get value from below.
  if(nextCache) {
    CacheResult *resultFromBelow = nextCache->read(firstInLine(address), contents->at(0)->at(0)->size());
    for(int i = 0; i < contents->at(0)->at(0)->size(); i++) {
      contents->at(index)->at(way)->at(i) = resultFromBelow->result.at(i);
    }
    wait += resultFromBelow->time;
    // This is newly fetched, so it's clean.
    dirty->at(index)->at(way) = 0;
    delete resultFromBelow;
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

string Cache::toTable() {
  stringstream result;
  result << "tag\tind\tdirty\tLRU\tvalid\tD0add\t";
  for(int offset = 0; offset < contents->at(0)->at(0)->size(); offset++) {
    result << "D" << offset << "\t";
  }
  result << endl;
  for(int ind = 0; ind < contents->size(); ind++) {
    for(int way = 0; way < contents->at(0)->size(); way++) {
      result 
        << tags->at(ind)->at(way) << "\t" 
        << ind << "\t" 
        << dirty->at(ind)->at(way) << "\t"
        << LRU->at(ind)->at(way) << "\t"
        << valid->at(ind)->at(way) << "\t"
        << buildAddress(tags->at(ind)->at(way), ind, 0) << "\t";
      for(int offset = 0; offset < contents->at(0)->at(0)->size(); offset++) {
        result << contents->at(ind)->at(way)->at(offset) << "\t";
      }
      result << endl;
    }
  }
  return result.str();
}
