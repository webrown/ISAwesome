#include "Cache.h"
#include <iostream>

using namespace std;

Cache::Cache( int tagBits, int indexBits, int logDataWordCount, int logAssociativity, float delay, Cache *prevCache, Cache *nextCache) {
  this->tagBits = tagBits;
  this->indexBits = indexBits;
  this->logDataWordCount = logDataWordCount;
  this->prevCache = prevCache;
  this->nextCache = nextCache;
  this->delay = delay;
  this->logAssociativity = logAssociativity;
  cout << "Cache done! :D" << endl;
}

CacheResult *Cache::read(unsigned int address, unsigned int length){
  vector<int> *data;
  data = new vector<int>();
  CacheResult *result = new CacheResult(*data, 42);
  return result;
}

float Cache::write(vector<int> *value, unsigned int address){
  return 42;
}

string *Cache::save(){
  string *result = new string("42");
  return result;
}

void Cache::restore(string *xml){
}


