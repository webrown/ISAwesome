#ifndef SERIALIZER_H
#define SERIALIZER_H
#include <QVector>
#include <QString>

QString *serialize(QVector<int>* const input);
QVector<int> *deserialize(QString* const input);

#endif
