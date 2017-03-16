#ifndef QUERY_RESULT_H
#define QUERY_RESULT_H
#include <QVector>
enum Type{
    INTEGER, FLOAT
};

using namespace std;
class QueryResult{
  public:
    Type type;
    QVector<int> result;
    QVector<float> result2;
    double time;

    QueryResult(QVector<int> result, double time);
    QueryResult(QVector<float> result, double time);
    int at(int index);
    size_t size();
};
#endif
