#include "QueryResult.h"
#include <QDebug>
QueryResult::QueryResult(QVector<int> result, double time) {
  this->result = result;
  this->time = time;
  this->type = INTEGER;
}
QueryResult::QueryResult(QVector<float> result, double time){
  this->result2 = result;
  this->time = time;
  this->type = FLOAT;
}

int QueryResult::at(int i) {
  if(this->type != INTEGER) {
    qDebug() << "int requested from non-int QueryResult.";
    exit(-1);
  }
  return this->result.at(i);
}

//float QueryResult::at(int i) {
//  if(this->type != FLOAT) {
//    qDebug() << "float requested from non-float QueryResult.";
//    exit(-1);
//  }
//  return this->result2.at(i);
//}

size_t QueryResult::size() {
  if(this->type == INTEGER) return this->result.size();
  if(this->type == FLOAT) return this->result2.size();
  qDebug() << "QueryResult is not INTEGER or FLOAT.  wuuuut???";
  exit(-1);
}
