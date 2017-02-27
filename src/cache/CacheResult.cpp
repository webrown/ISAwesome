#include "CacheResult.h"
CacheResult::CacheResult(vector<int> result, double time) {
  this->result = result;
  this->time = time;
}

int CacheResult::getIntForm() {
  return this->result.at(0);
}
