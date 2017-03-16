#include "Cache.h"
#include "QueryResult.h"
#include <stdlib.h>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <fstream>
#include <QTextStream>
#include <QFile>

QTextStream cin(stdin);
QTextStream cout(stdout);

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

  cout << "add|a|push indexBits offsetBits wayBits delay" << endl;
  cout << "Example: a 4 0 0 5.1" << endl;
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

  cout << "fwrite|save fileName" << endl;
  cout << "Example: fwrite state.ccs" << endl;
  cout << "Saves state of top cache to a file." << endl;
  cout << endl;

  cout << "fread|restore fileName" << endl;
  cout << "Example: fread state.ccs" << endl;
  cout << "Sets state of top cache.  Make sure cache dimensions match!" << endl;
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
  QString input;
  while(true) {
    cout << ">>>";
    cout.flush();
    input = cin.readLine();
    QStringList tokens = input.split(' ');
    // If this is a generate request, build the new cache level!
    if(tokens.size() == 0) {
      continue;
    }
    if(tokens[0] == "push" || tokens[0] == "a" || tokens[0] == "add") {
      if(tokens.size() == 5) {
        cout << "Created cache:" << endl;
        cout << "  Index Bits = " << tokens[1] << endl;
        cout << "  Offset Bits = " << tokens[2] << endl;
        cout << "  Way Bits = " << tokens[3] << endl;
        cout << "  Delay = " << tokens[4] << endl;
        topCache = new Cache(tokens[1].toInt(), tokens[2].toInt(), tokens[3].toInt(), tokens[4].toFloat(), topCache);
        showCaches();
      }
      else {
        cout << "I want 4 parameters for that." << endl;
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
    else if(tokens[0] == "fwrite" || tokens[0] == "save") {
      if(tokens.size() == 2) {
        if(topCache == NULL) {
          cout << "No cache to save." << endl;
        }
        else {
          QString fileName = tokens[1];
          QFile outputFile(fileName);
          outputFile.open(QIODevice::ReadWrite);
          QTextStream output(&outputFile);
          QString *state = topCache->save();
          output << *state;
          output.flush();
          outputFile.close();
          cout << "Wrote state to " << fileName << "." << endl;
          cout << *state << endl;
          delete state;
        }
      }
      else {
        cout << "Must have exactly 1 parameter." << endl;
      }
    }
    else if(tokens[0] == "fread" || tokens[0] == "restore") {
      if(tokens.size() == 2) {
        if(topCache == NULL) {
          cout << "No cache to read into." << endl;
        }
        else {
          QString fileName = tokens[1];
          QFile file(fileName);
          file.open(QIODevice::ReadWrite);
          QString state;
          QTextStream in(&file);
          state = in.readAll();
          file.close();
          topCache->restore(&state);
          showCaches();
          cout << "Read state from " << fileName << "." << endl;
          cout << state << endl;
        }
      }
      else {
        cout << "Must have exactly 1 parameter." << endl;
      }
    }
    else if(tokens[0] == "write" || tokens[0] == "w") {
      if(tokens.size() > 2) {
        if(topCache == NULL) {
          cout << "No cache to write to." << endl;
        }
        else {
          QVector<int> values;
          cout << "Writting < ";
          for( int i = 1; i < tokens.size()-1; i++) {
            cout << tokens[i] << " ";
            values.push_back(tokens[i].toInt());
          }
          int address = tokens[tokens.size()-1].toInt();
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
          int address = tokens[1].toInt();
          int length = 1;
          if(tokens.size() == 3) {
            length = tokens[2].toInt();
          }
          if(length == 1) {
            cout << "Reading address " << address << "." << endl;
          }
          else {
            cout << "Reading addresses between " << address << " and " << (address+length-1) << "." << endl;
          }
          QueryResult *res = topCache->read(address, length);
          showCaches();
          // Print what you found.
          cout << "After a wait of " << res->time << ", got < ";
          for(size_t i = 0; i < res->size(); i++) {
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
