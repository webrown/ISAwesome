#ifndef REGISTER_H
#define REGISTER_H

#include "QueryResult.h"
#include "MemoryInterface.h"
#include <QString>
#include "../architecture.h"

class Register : MemoryInterface{
    public:
        using MemoryInterface::write;
        //QVector<int> _iScas;
        //QVector<int> _sRegs;
        //QVector<float> _fScas;
        //QVector< QVector <int> > _iVecs;
        //QVector< QVector <float> > _fVecs;
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

        //double write(QVector<int> *value, unsigned int address);
        //double write(int value, unsigned int address);
        double write(QVector<Value> *value, unsigned int address);
        double write(Value value, unsigned int address);
        QString *save();
        void restore(QString *state);
};

#endif
