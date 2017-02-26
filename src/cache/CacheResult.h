#ifndef CACHE_RESULT_H
#define CACHE_RESULT_H
#include <vector>
using namespace std;
class CacheResult{
  public:
    vector<int> result;
    double time;
    CacheResult(vector<int> result, double time);
};
#endif
