#include "QueryResult.h"
#include <QDebug>
QueryResult::QueryResult(QVector<int> result, double time) {
  QVector<Value> newResult(result.size());
  for(int i = 0; i < result.size(); i++) {
    newResult[i].asInt = result.at(i);
  }
  this->result = newResult;
  this->time = time;
}

QueryResult::QueryResult(QVector<float> result, double time){
  QVector<Value> newResult(result.size());
  for(int i = 0; i < result.size(); i++) {
    newResult[i].asFloat = result.at(i);
  }
  this->result = newResult;
  this->time = time;
}

QueryResult::QueryResult(QVector<Value> result, double time){
  this->result = result;
  this->time = time;
}

Value QueryResult::at(int i) {
  return this->result.at(i);
}

size_t QueryResult::size() {
  return this->result.size();
}
