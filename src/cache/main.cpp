#include "Cache.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

int main() {
cout << "  ____                       _            ____           _          " << endl;
cout << " / ___|_ __ _   _ _ __   ___| |__  _   _ / ___|__ _  ___| |__   ___ " << endl;
cout << "| |   | '__| | | | '_ \\ / __| '_ \\| | | | |   / _` |/ __| '_ \\ / _ \\" << endl;
cout << "| |___| |  | |_| | | | | (__| | | | |_| | |__| (_| | (__| | | |  __/" << endl;
cout << " \\____|_|   \\__,_|_| |_|\\___|_| |_|\\__, |\\____\\__,_|\\___|_| |_|\\___|" << endl;
cout << "                                   |___/    " << endl;
  cout << endl;
  cout << "By Youngkyun Lee and Walter Brown" << endl;

  Cache l1Cache(5,3,2, 2, 10, NULL, NULL);
  return 0;
}
