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
    bool has(Value v, FlagType f){
        return (f & v.asUInt) != 0;
    }
    QBitArray has(QVector<Value> v, FlagType f){
        QBitArray ret(VECTOR_SIZE);
        for(int i =0; i < VECTOR_SIZE; i++){
            bool bit = (f & v[i].asUInt) != 0;
            ret.setBit(i, bit);
        }
        return ret;
    }

    void add(Value v, FlagType f){
        v = {(v.asUInt | f)};
    }
    void add(QVector<Value> v, FlagType f){
        for(int i = 0; i < VECTOR_SIZE; i++){
            v[i] = {(v[i].asUInt | f)};
        }
    }

    void remove(Value v, FlagType f){
        v = {(v.asUInt & ~f)};
    }
    void remove(QVector<Value> v, FlagType f){
        for(int i = 0; i < VECTOR_SIZE; i++){
            v[i] = {(v[i].asUInt & ~f)};
        }
    }

};
#endif
