#ifndef FLAG_H
#define FLAG_H 
#include "Value.h"
#include <QVector>
#include <QBitArray>
#include "../computer/Architecture.h"

namespace Flag{
    enum FlagType{
        EQ = 0, NE =1, CS=2,CC=4, MI=8,PL=16,VS=32,VC=64,DZ=128,NZ=256,LE=512,GE=1024,LT=2048,GT=4096,AL=8192,UN=16384
    };
    bool has(Value v, FlagType f);
    QBitArray has(QVector<Value> v, FlagType f);
    Value add(Value v, FlagType f);
    QVector<Value> add(QVector<Value> v, FlagType f);
    Value remove(Value v, FlagType f);
    QVector<Value> remove(QVector<Value> v, FlagType f);
};
#endif
