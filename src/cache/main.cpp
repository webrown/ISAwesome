#include "Cache.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

int main() {
  {
    Cache l1Cache(3,5,6, 2, 10, NULL, NULL);
    Cache l2Cache(3,5,6, 2, 10, &l1Cache, NULL);
    Cache l3Cache(3,5,6, 2, 10, &l2Cache, NULL);
    l2Cache.nextCache = &l3Cache;
    l1Cache.nextCache = &l2Cache;

  }
  return 0;
}
