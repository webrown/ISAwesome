#include "QueryResult.h"
QueryResult::QueryResult(QVector<int> result, double time) {
  this->result = result;
  this->time = time;
}
QueryResult::QueryResult(QVector<float> result, double time){
    this->result2 = result;
    this->time = time;
}

int QueryResult::at(int i) {
  return this->result.at(i);
}

size_t QueryResult::size() {
  return this->result.size();
}
