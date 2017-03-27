#ifndef FLAG_H
#define FLAG_H 
#include "Value.h"
#include <QVector>
#include <QBitArray>
#include "../computer/Architecture.h"

namespace Flag{
    enum FlagType{
        EQ = 1, NE =2, CS=4,CC=8, MI=16,PL=32,VS=64,VC=128,DZ=256,NZ=512,LE=1024,GE=2048,LT=4096,GT=8192,AL=16384,UN=32768
    };
    bool has(Value v, FlagType f);
    QBitArray has(QVector<Value> v, FlagType f);
    Value add(Value v, FlagType f);
    QVector<Value> add(QVector<Value> v, FlagType f);
    Value remove(Value v, FlagType f);
    QVector<Value> remove(QVector<Value> v, FlagType f);
};
#endif
