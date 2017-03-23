#include "Cache.h"
#include "serialization.h"
#include <iostream>
#include <algorithm>
#include <sstream>

using namespace std;

Cache::Cache(int indexBits, int logDataWordCount, int logAssociativity, double delay, Cache *nextMemory) {
  type = BOTH;
  // Load in params.
  this->indexBits = indexBits;
  this->logDataWordCount = logDataWordCount;
  this->nextMemory = nextMemory;
  this->delay = delay;
  this->logAssociativity = logAssociativity;

  // Set up the cache QVectors.
  tags = new QVector< QVector<int> * >();
  contents = new QVector< QVector< QVector<Value> * > * >();
  LRU = new QVector< QVector<int> * >();
  dirty = new QVector< QVector<int> * >();
  valid = new QVector< QVector<int> * >();
  size_t maxIndex = 1 << indexBits;
  size_t ways = 1 << logAssociativity;
  size_t dataWordCount = 1 << logDataWordCount;
  for(size_t index = 0; index < maxIndex; index++) {
    // Add tag bits.
    tags->push_back(new QVector<int>(ways, 0));
    // Add content cells.
    QVector< QVector<Value> * > *newContent = new QVector<QVector<Value> * >();
    for(size_t way = 0; way < ways; way++) {
      Value v = {0};
      newContent->push_back(new QVector<Value>(dataWordCount, v));
    }
    contents->push_back(newContent);
    // Add LRU bit
    LRU->push_back(new QVector<int>(ways, 0));
    // Add dirty bit
    dirty->push_back(new QVector<int>(ways, 0));
    // Add valid bit
    valid->push_back(new QVector<int>(ways, 0));
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

QueryResult *Cache::read(unsigned int address, unsigned int length){
  // Hardware constraint:  Can't parallel load more values than there are in the cache.
  size_t mL = maxLength(address);
  if(length > mL) {
    length = mL;
    cout << "WARNING:  read given too large a QVector, shrinking size to " << mL << "." << endl;
  }
  double wait = delay;
  // Get these values into the cache if they are not already.
  double fetchWait = 0;
  QVector<Value> *data = new QVector<Value>();
  for(unsigned int i = address; i < address+length; i++) {
    // TODO May be able to be optimized later; often tag and index won't change for long periods of time.
    fetchWait = max(fetchWait, fetch(i));
    // Now at front of LRU queue
    updateLRU(i);
    // Read value.
    int way = addressWay(i);
    QVector<int> *tagIndOff = splitAddress(i);
    int index = tagIndOff->at(1);
    int offset = tagIndOff->at(2);
    delete tagIndOff;
    data->push_back(contents->at(index)->at(way)->at(offset));
  }
  // All fetches happened in parallel.
  wait += fetchWait;
  QueryResult *result = new QueryResult(*data, wait);
  delete data;
  return result;
}

QueryResult *Cache::read(unsigned int address){
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

double Cache::write(QVector<Value> *_value, unsigned int address){
  int mL = maxLength(address);
  int mustDeleteValue = 0;
  if(_value->size() > mL) {
    QVector<Value>* value = new QVector<Value>(mL);
      for(int i = 0; i < mL; i++){
          value->append(_value->at(i));
      } 
      _value = value;
    // You'll have to clean up this new QVector later!
    mustDeleteValue = 1;
    cout << "WARNING:  write given too large a QVector, shrinking size to " << mL << "." << endl;
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
  for(int i = 0; i < _value->size(); i++) {
    fetchWait = max(fetchWait, fetch(address+i));
    // Move up in LRU queue.
    updateLRU(address+i);
    // If this is going to change the value, the value is becoming dirty.
    QVector<int> *tagIndOff = splitAddress(address+i);
    int index = tagIndOff->at(1);
    int offset = tagIndOff->at(2);
    delete tagIndOff;
    int way = addressWay(address+i);
    if(contents->at(index)->at(way)->at(offset).i != _value->at(i).i) {
      dirty->at(index)->replace(way,1);
      // Write to the specified index.
      contents->at(index)->at(way)->replace(offset,_value->at(i));
    }
  }
  wait += fetchWait;
  if(mustDeleteValue) {
    delete _value;
  }
  // Tell the layer above how long this took.
  return wait;
}

int Cache::addressWay(unsigned int address){
  // Returns the associative way that a certain address is at.
  // If there is no way, return -1.
  QVector<int> *tagIndOff = splitAddress(address);
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

double Cache::write(Value input, unsigned int address){
  QVector<Value> *tinyQVector = new QVector<Value>(1, input);
  double result = write(tinyQVector, address);
  delete tinyQVector;
  return result;
}

QString *Cache::save(){
  QVector<int> v;
  for(int ind = 0; ind < contents->size(); ind++) {
    for(int way = 0; way < contents->at(0)->size(); way++) {
      // Record contents
      for(int offset = 0; offset < contents->at(0)->at(0)->size(); offset++) {
        v.push_back(contents->at(ind)->at(way)->at(offset).toInt);
      }
      // Record dirty
      v.push_back(dirty->at(ind)->at(way));
      // Record LRU
      v.push_back(LRU->at(ind)->at(way));
      // Record tag
      v.push_back(tags->at(ind)->at(way));
      // Record valid
      v.push_back(valid->at(ind)->at(way));
    }
  }
  return serialize(&v);
}

void Cache::restore(QString *state){
  if(!state) {
    return;
  }
  QVector<int> *s = deserialize(state);
  int stateIndex = 0;
  for(int ind = 0; ind < contents->size(); ind++) {
    for(int way = 0; way < contents->at(0)->size(); way++) {
      // Place contents.
      for(int offset = 0; offset < contents->at(0)->at(0)->size(); offset++) {
        if(stateIndex == s->size()) {
          return;
        }
        Value value = {s->at(stateIndex++)};
        contents->at(ind)->at(way)->replace(offset, value);
      }
      // Place in dirty.
      if(stateIndex == s->size()) {
        return;
      }
      dirty->at(ind)->replace(way,s->at(stateIndex++));
      // Place in LRU.
      if(stateIndex == s->size()) {
        return;
      }
      LRU->at(ind)->replace(way,s->at(stateIndex++));
      // Place in tag.
      if(stateIndex == s->size()) {
        return;
      }
      tags->at(ind)->replace(way,s->at(stateIndex++));
      // Place in valid.
      if(stateIndex == s->size()) {
        return;
      }
      valid->at(ind)->replace(way,s->at(stateIndex++));
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
  QVector<int> *tagIndOff = splitAddress(address);
  int index = tagIndOff->at(1);
  delete tagIndOff;
  // What is your current spot in the queue?
  int queuePosition = LRU->at(index)->at(way);
  // Anyone in font of you just got cut.
  for(int i = 0; i < LRU->at(0)->size(); i++) {
    if(LRU->at(index)->at(i) <= queuePosition) {
      LRU->at(index)->replace(i, LRU->at(index)->at(i)+1);
    }
  }
  // Move to the front of the queue.
  LRU->at(index)->replace(way, 0);
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
  QVector<int> *tagIndOff = splitAddress(address);
  int index = tagIndOff->at(1);
  int tag = tagIndOff->at(0);
  delete tagIndOff;
  // At this point, an eviction is needed.
  // Find the item with the worst LRU
  way = getLRUWay(index);
  // What is the first address on the evicted line?
  int firstEvictedAddress = buildAddress(tags->at(index)->at(way), index, 0);
  // Write to the cache below if dirty and able.
  if(dirty->at(index)->at(way) && nextMemory) {
    wait += nextMemory->write(contents->at(index)->at(way), firstEvictedAddress);
  }
  // Set tag and valid bits
  tags->at(index)->replace(way, tag);
  valid->at(index)->replace(way, 1);
  // Get value from below.
  if(nextMemory) {
    QueryResult *resultFromBelow = nextMemory->read(firstInLine(address), contents->at(0)->at(0)->size());
   for(int i = 0; i < contents->at(0)->at(0)->size(); i++) {
      contents->at(index)->at(way)->replace(i,resultFromBelow->result.at(i));
    }
    wait += resultFromBelow->time;
    // This is newly fetched, so it's clean.
    dirty->at(index)->replace(way,0);
    delete resultFromBelow;
  }
  return wait;
}


QVector<int> *Cache::splitAddress(unsigned int address){
  // Returns three-long QVector:
  // [0] - tag
  // [1] - index
  // [2] - offset
  QVector<int> *result = new QVector<int>();
  result->push_back(address >> (indexBits + logDataWordCount));
  result->push_back((address >> (logDataWordCount)) % (1 << indexBits));
  result->push_back(address % (1 << (logDataWordCount)));
  return result;
}

QString Cache::toTable() {
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
        result << contents->at(ind)->at(way)->at(offset).i << "\t";
      }
      result << endl;
    }
  }
  return QString(result.str().c_str());
}
