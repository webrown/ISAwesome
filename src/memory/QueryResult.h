#ifndef QUERY_RESULT_H
#define QUERY_RESULT_H
#include <QVector>
#include "Value.h"

using namespace std;
class QueryResult{
  public:
    QVector<Value> result;
    double time;

    QueryResult(QVector<int> result, double time);
    QueryResult(QVector<float> result, double time);
    QueryResult(QVector<Value> result, double time);
    Value at(int index);
    size_t size();
};
#endif
