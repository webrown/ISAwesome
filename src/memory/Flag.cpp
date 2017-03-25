#include "Flag.h"
namespace Flag{
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

    Value add(Value v, FlagType f){
        v = {(v.asUInt | f)};
        return v;
    }
    QVector<Value> add(QVector<Value> v, FlagType f){
        for(int i = 0; i < VECTOR_SIZE; i++){
            v[i] = {(v[i].asUInt | f)};
        }
        return v;
    }

    Value remove(Value v, FlagType f){
        v = {(v.asUInt & ~f)};
        return v;
    }
    QVector<Value> remove(QVector<Value> v, FlagType f){
        for(int i = 0; i < VECTOR_SIZE; i++){
            v[i] = {(v[i].asUInt & ~f)};
        }
        return v;
    }
};
