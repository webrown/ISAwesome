#ifndef REGISTER_H
#define REGISTER_H

#include "QueryResult.h"
#include <QString>
#include "../computer/Architecture.h"

class Register{
    public:
        QVector<Value> _scas;
        QVector< QVector <Value> > _vecs;
        Value _flag; 
        QVector<Value> _flags;

        Register();
        ~Register();
        void init();

        uint getPC();
        uint getSP();
        uint getBP();
        uint getLR();
        

        Value read(int i);
        QVector<Value> readVector(int address);

        //Scalar write
        void write(Value v, int address);
        void write(int v, int address);
        void write(unsigned int v, int address);
        void write(float v, int address);


        //Vector write
        void writeVector(QVector<Value> v, int address);
        void writeVector(QVector<int> v, int address);
        void writeVector(QVector<float> v, int address);

        void write(QVector<Value> v, int address);
        void write(QVector<int> v, int address);
        void write(QVector<float> v, int address);

        //flag write

        Value readFlag();
        void writeFlag(Value v);
        QVector<Value> readFlags();
        void writeFlags(QVector<Value> v);



        QByteArray save();
        void restore(QByteArray state);

        static const unsigned int scalarIntegers = 0;
        static const unsigned int scalarFloats = 10;
        static const unsigned int specials = 20;
        static const unsigned int vectorIntegers = 24;
        static const unsigned int vectorFloats = 28;

        static const unsigned int LR = 20;
        static const unsigned int SP = 21;
        static const unsigned int BP = 22;
        static const unsigned int PC = 23;
        static bool isVectorIndex(int index);
        static bool isFloatIndex(int index);
};

#endif
