#ifndef REGISTER_H
#define REGISTER_H

#include "QueryResult.h"
#include "MemoryInterface.h"
#include <QString>
#include "../Architecture.h"

class Register : MemoryInterface{
    public:
<<<<<<< HEAD
        QVector<int> _iScas;
        QVector<int> _sRegs;
        QVector<float> _fScas;
        QVector< QVector <int> > _iVecs;
        QVector< QVector <float> > _fVecs;
        const double delay = 0;
=======
        using MemoryInterface::write;
        QVector<Value> _iScas;
        QVector<Value> _sRegs;
        QVector<Value> _fScas;
        QVector< QVector <Value> > _iVecs;
        QVector< QVector <Value> > _fVecs;
        static const double delay = 0;
>>>>>>> 339ecf0787838d644c43f9128079d2177e8a57f8

        Register();
        ~Register();
        QueryResult *read(unsigned int address, unsigned int length);
        QueryResult *read(unsigned int address);

        double write(QVector<Value> *value, unsigned int address);
        double write(Value value, unsigned int address);
        QString *save();
        void restore(QString *state);

        static const unsigned int scalarIntegers = 0;
        static const unsigned int scalarFloats = 10;
        static const unsigned int specials = 20;
        static const unsigned int vectorIntegers = 24;
        static const unsigned int vectorFloats = 28;

        static const unsigned int LR = 20;
        static const unsigned int SP = 21;
        static const unsigned int BP = 22;
        static const unsigned int PC = 23;
};

#endif
