#include "../src/memory/serialization.h"

#include <QDebug>
#include <stdlib.h>
#include <QString>

using namespace std;

void compareQVectors(QString testName, QVector<int> vec1, QVector<int> vec2){
  qDebug() << "Testing" << testName;
  bool diffFound = false;
  if(vec1.size() != vec2.size()) {
    diffFound = true;
    qDebug() << "FAIL: Size of" << vec1.size() << "vs" << vec2.size();
  }
  else {
    // Try to compare pointwise.
    for(int i = 0; i < vec1.size(); i++) {
      if(vec1.at(i) != vec2.at(i)) {
        diffFound = true;
        qDebug() << "FAIL: Mismatch at index" << i << "it's" << vec1.at(i) << "vs" << vec2.at(i);
      }
    }
  }
  if(diffFound) {
    qDebug() << "FAIL: " << testName;
    // Do an exhaustive dump
    for(int i = 0; i < max(vec1.size(), vec2.size()); i++) {
      QString resString = "[" + QString::number(i) + "]          " ;
      if(vec1.size() > i) resString += QString::number(vec1.at(i));
      else resString += " ";
      resString += "          ";
      if(vec2.size() > i) resString += QString::number(vec2.at(i));
      qDebug() << resString;
    }
  }
  else {
    qDebug() << "PASS: " << testName;
  }
  qDebug() << "Done testing" << testName;
}

int main() {
  qDebug() << "Want to test serialization.";
  {
    QVector<int> oldState;
    QByteArray storage;
    QVector<int> newState;

    oldState.push_back(1);
    oldState.push_back(2);
    oldState.push_back(3);
    oldState.push_back(4);
    oldState.push_back(5);

    serialize(&storage, &oldState);
    deserialize(&storage, &newState);
    //newState[1] = 1000;
    compareQVectors("Simple 1-5", oldState, newState);
  }

  {
    QVector<int> oldState;
    QByteArray storage;
    QVector<int> newState;

    oldState.push_back(-1);
    oldState.push_back(-2);
    oldState.push_back(-3);
    oldState.push_back(-4);
    oldState.push_back(-5);

    serialize(&storage, &oldState);
    deserialize(&storage, &newState);
    compareQVectors("Negatives", oldState, newState);
  }

  {
    // See if serialization distinguishes between two suspicious numbers.
    QVector<int> oldState1;
    QByteArray storage1;

    QVector<int> oldState2;
    QByteArray storage2;

    oldState1.push_back(4286578688);
    oldState2.push_back(1065353216);

    serialize(&storage1, &oldState1);
    serialize(&storage2, &oldState2);

    bool foundDifference = false;
    for(int i = 0; i < storage1.size(); i++) {
      if(storage1.at(i) != storage2.at(i)) foundDifference = true;
    }
    if(foundDifference) {
      qDebug() << "PASS: different values encode bytearrays differently";
    }
    else {
      qDebug() << "FAIL: different values encode bytearrays the same";
    }
  }

  {
    QVector<int> oldState;
    QByteArray storage;
    QVector<int> newState;

    oldState.push_back(0x1f);
    oldState.push_back(-4);
    oldState.push_back(4286578688);
    oldState.push_back(1065353216);

    serialize(&storage, &oldState);
    deserialize(&storage, &newState);
    compareQVectors("Young Case", oldState, newState);
  }
}
