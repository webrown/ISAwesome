#ifndef REGISTER_H
#define REGISTER_H

#include "QueryResult.h"
#include "MemoryInterface.h"
#include <QString>
#include "../computer/Architecture.h"

class Register : MemoryInterface{
    public:
        using MemoryInterface::write;

        QVector<Value> _scas;
        QVector< QVector <Value> > _vecs;
        Value _flag; 
        QVector<Value> _flags;

        Register();
        ~Register();
        uint getPC();
        uint getSP();
        uint getBP();
        uint getLR();

        Value read(int i);
        void write(int address, Value v);

        QVector<Value> readVector(int address);
        void writeVector(int address, QVector<Value> v);

        Value readFlag();
        void writeFlag(Value v);
        QVector<Value> readFlags();
        void writeFlags(QVector<Value> v);



        QString *save();
        void restore(QString *state);

        static const unsigned int scalarIntegers = 0;
        static const unsigned int scalarFloats = 10;
        static const unsigned int specials = 20;
        static const unsigned int vectorIntegers = 24;
        static const unsigned int vectorFloats = 28;
        static const unsigned int flags = 33;

        static const unsigned int LR = 20;
        static const unsigned int SP = 21;
        static const unsigned int BP = 22;
        static const unsigned int PC = 23;

        //Deprecated
        static constexpr double delay = 0;
        double write(QVector<Value> *value, unsigned int address);
        double write(Value value, unsigned int address);
        QueryResult *read(unsigned int address, unsigned int length);
        QueryResult *read(unsigned int address);
        QVector<Value> _iScas;
        QVector<Value> _fScas;
        QVector<Value> _sRegs;
        QVector<QVector<Value>> _iVecs;
        QVector<QVector<Value>> _fVecs;
        QVector<Value> _flagVec;
};

#endif
