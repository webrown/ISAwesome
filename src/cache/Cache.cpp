#include "Cache.h"
#include <iostream>

using namespace std;

Cache::Cache( int tag_bits, int index_bits, int log_data_word_count, float delay, Cache *prev_cache, Cache *next_cache) {
  this->tag_bits = tag_bits;
  this->index_bits = index_bits;
  this->log_data_word_count = log_data_word_count;
  this->prev_cache = prev_cache;
  this->next_cache = next_cache;
  this->delay = delay;
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


