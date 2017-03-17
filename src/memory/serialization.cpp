#include "serialization.h"

QString *serialize(QVector<int>* const input) {
  QString *result = new QString();
  for(int i = 0; i < input->size(); i++) {
    // Write this int.
    *result += (input->at(i) & 0x000000ff) >>  0;
    *result += (input->at(i) & 0x0000ff00) >>  8;
    *result += (input->at(i) & 0x00ff0000) >> 16;
    *result += (input->at(i) & 0xff000000) >> 24;
  }
  return result;
}

QVector<int> *deserialize(QString* const input) {
  QVector<int> *result = new QVector<int>();
  for(int i = 0; i < input->size(); i+=4) {
    // Rebuild number.
    result->push_back(
      input->at(i+0).cell() <<  0 |
      input->at(i+1).cell() <<  8 |
      input->at(i+2).cell() << 16 |
      input->at(i+3).cell() << 24 
    );
  }
  return result;
}

