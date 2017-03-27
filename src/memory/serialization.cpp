#include "serialization.h"

void serialize(QByteArray* result, QVector<int>* const input) {
  for(int i = 0; i < input->size(); i++) {
    // Write this int.
    *result += (input->at(i) & 0x000000ff) >>  0;
    *result += (input->at(i) & 0x0000ff00) >>  8;
    *result += (input->at(i) & 0x00ff0000) >> 16;
    *result += (input->at(i) & 0xff000000) >> 24;
  }
}
void deserialize(QByteArray* const input, QVector<int>* result) {
  for(int i = 0; i < input->size(); i+=4) {
    // Rebuild number.
    result->push_back(
      input->at(i+0) <<  0 |
      input->at(i+1) <<  8 |
      input->at(i+2) << 16 |
      input->at(i+3) << 24 
    );
  }
}


void serialize(QByteArray* result, QVector<uint>* const input) {
  for(int i = 0; i < input->size(); i++) {
    // Write this int.
    *result += (input->at(i) & 0x000000ff) >>  0;
    *result += (input->at(i) & 0x0000ff00) >>  8;
    *result += (input->at(i) & 0x00ff0000) >> 16;
    *result += (input->at(i) & 0xff000000) >> 24;
  }
}
void deserialize(QByteArray* const input, QVector<uint>* result) {
  for(int i = 0; i < input->size(); i+=4) {
    // Rebuild number.
    result->push_back(
      input->at(i+0) <<  0 |
      input->at(i+1) <<  8 |
      input->at(i+2) << 16 |
      input->at(i+3) << 24 
    );
  }
}

