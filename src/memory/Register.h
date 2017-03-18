#ifndef REGISTER_H
#define REGISTER_H

#include "QueryResult.h"
#include "MemoryInterface.h"
#include <QString>
#include "../architecture.h"

class Register : MemoryInterface{
    public:
        using MemoryInterface::write;
        QVector<Value> _iScas;
        QVector<Value> _sRegs;
        QVector<Value> _fScas;
        QVector< QVector <Value> > _iVecs;
        QVector< QVector <Value> > _fVecs;
        static const double delay = 0;

        Register();
        ~Register();
        QueryResult *read(unsigned int address, unsigned int length);
        QueryResult *read(unsigned int address);

        double write(QVector<Value> *value, unsigned int address);
        double write(Value value, unsigned int address);
        QString *save();
        void restore(QString *state);

        static const unsigned int LR = 20;
        static const unsigned int SP = 21;
        static const unsigned int BP = 22;
        static const unsigned int PC = 23;
};

#endif
