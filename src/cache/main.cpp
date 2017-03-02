#include "Cache.h"
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <stdlib.h>

using namespace std;

Cache *topCache = NULL;

void showCaches() {
  Cache *iter = topCache;
  while(iter) {
    cout << iter->toTable() << endl;
    iter = iter->nextCache;
  }
}

void showHelp() {
  cout << "help|h" << endl;
  cout << "Example: h" << endl;
  cout << "Show this help." << endl;
  cout << endl;
  cout << "add|a|push tagBits indexBits offsetBits wayBits delay" << endl;
  cout << "Example: a 0 4 0 0 5.1" << endl;
  cout << "Adds a new cache above the last one." << endl;
  cout << endl;
  cout << "pop|subtract|s" << endl;
  cout << "Example: pop" << endl;
  cout << "Removes the top cache." << endl;
  cout << endl;
  cout << "write|w value1 value2 value3... address" << endl;
  cout << "Example: write 4 9" << endl;
  cout << "Parallel-writes the values to a vector starting at address." << endl;
  cout << endl;
  cout << "read|r address [length]" << endl;
  cout << "Example: read 4" << endl;
  cout << "Parallel-reads starting from address and going to specified length." << endl;
  cout << endl;
  cout << "exit|e|quit|q" << endl;
  cout << "Example: exit" << endl;
  cout << "Exit the program" << endl;
  cout << endl;
}

int main() {
  cout << "Welcome to" << endl;
  cout << "  ____                       _            ____           _          " << endl;
  cout << " / ___|_ __ _   _ _ __   ___| |__  _   _ / ___|__ _  ___| |__   ___ " << endl;
  cout << "| |   | '__| | | | '_ \\ / __| '_ \\| | | | |   / _` |/ __| '_ \\ / _ \\" << endl;
  cout << "| |___| |  | |_| | | | | (__| | | | |_| | |__| (_| | (__| | | |  __/" << endl;
  cout << " \\____|_|   \\__,_|_| |_|\\___|_| |_|\\__, |\\____\\__,_|\\___|_| |_|\\___|" << endl;
  cout << "                                   |___/    " << endl;
  cout << "Goes well with PISA!" << endl;
  cout << endl;
  cout << "By Youngkyun Lee and Walter Brown" << endl;
  cout << endl;

  showHelp();

  // Main loop
  string input;
  while(true) {
    cout << ">>>";
    getline(cin, input);
    stringstream inputStream(input);
    string token;
    vector<string> tokens;
    while(getline(inputStream, token, ' ')) {
      tokens.push_back(token);
    }
    // If this is a generate request, build the new cache level!
    if(tokens.size() == 0) {
      continue;
    }
    if(tokens[0] == "push" || tokens[0] == "a" || tokens[0] == "add") {
      if(tokens.size() == 6) {
        cout << "Created cache:" << endl;
        cout << "  Tag Bits = " << tokens[1] << endl;
        cout << "  Index Bits = " << tokens[2] << endl;
        cout << "  Offset Bits = " << tokens[3] << endl;
        cout << "  Way Bits = " << tokens[4] << endl;
        cout << "  Delay = " << tokens[5] << endl;
        topCache = new Cache(atoi(tokens[1].c_str()), atoi(tokens[2].c_str()), atoi(tokens[3].c_str()), atoi(tokens[4].c_str()), atof(tokens[5].c_str()), topCache);
        showCaches();
      }
      else {
        cout << "I want 5 parameters for that." << endl;
      }
    }
    else if(tokens[0] == "pop" || tokens[0] == "s" || tokens[0] == "subtract") {
      if(tokens.size() == 1) {
        if(topCache == NULL) {
          cout << "No cache to pop." << endl;
        }
        else {
          cout << "Removed cache" << endl;
          Cache *removedCache = topCache;
          topCache = topCache->nextCache;
          delete removedCache;
          showCaches();
        }
      }
      else {
        cout << tokens[0] << " shouldn't have any parameters." << endl;
      }
    }
    else if(tokens[0] == "write" || tokens[0] == "w") {
      if(tokens.size() > 2) {
        if(topCache == NULL) {
          cout << "No cache to write to." << endl;
        }
        else {
          vector<int> values;
          cout << "Writting < ";
          for( int i = 1; i < tokens.size()-1; i++) {
            cout << tokens[i] << " ";
            values.push_back(atoi(tokens[i].c_str()));
          }
          int address = atoi(tokens[tokens.size()-1].c_str());
          if(values.size() == 1) {
            cout << "> to " << address << "." << endl;
          }
          else {
            cout << "> between " << address << " and " << (address+values.size()-1) << "." << endl;
          }
          double wait = topCache->write(&values, address);
          showCaches();
          cout << "Wrote after a wait of " << wait << "." << endl;
        }
      }
      else {
        cout << "Must have at least 2 parameters." << endl;
      }
    }
    else if(tokens[0] == "read" || tokens[0] == "r") {
      if(tokens.size() == 2 || tokens.size() == 3) {
        if(topCache == NULL) {
          cout << "No cache to read from." << endl;
        }
        else {
          vector<int> *values;
          int address = atoi(tokens[1].c_str());
          int length = 1;
          if(tokens.size() == 3) {
            length = atoi(tokens[2].c_str());
          }
          if(length == 1) {
            cout << "Reading address " << address << "." << endl;
          }
          else {
            cout << "Reading addresses between " << address << " and " << (address+length-1) << "." << endl;
          }
          CacheResult *res = topCache->read(address, length);
          showCaches();
          // Print what you found.
          cout << "After a wait of " << res->time << ", got < ";
          for(int i = 0; i < res->size(); i++) {
            cout << res->at(i) << " ";
          }
          cout << ">." << endl;
          delete res;
        }
      }
      else {
        cout << "Must have at least 2 parameters." << endl;
      }
    }
    else if(tokens[0] == "exit" || tokens[0] == "quit" || tokens[0] == "q" || tokens[0] == "e") {
      if(tokens.size() == 1) {
        exit(0);
      }
      else {
        cout << tokens[0] << " shouldn't have any parameters." << endl;
      }
    }
    else if(tokens[0] == "help" || tokens[0] == "h") {
      showHelp();
    }
    else {
      showHelp();
      cout << "I don't know what " << tokens[0] << " is." << endl;
    }
  }
  return 0;
}
