#include "CacheResult.h"
CacheResult::CacheResult(vector<int> result, double time) {
  this->result = result;
  this->time = time;
}

int CacheResult::at(int i) {
  return this->result.at(i);
}

size_t CacheResult::size() {
  return this->result.size();
}
