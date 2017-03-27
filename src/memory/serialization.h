#ifndef SERIALIZER_H
#define SERIALIZER_H
#include <QVector>
#include <QString>

void serialize(QByteArray* result, QVector<int>* const input);
void deserialize(QByteArray* const input, QVector<int>* result);
void serialize(QByteArray* result, QVector<uint>* const input);
void deserialize(QByteArray* const input, QVector<uint>* result);


#endif
