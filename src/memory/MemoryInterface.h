#ifndef MEMORYINTERFACE_H
#define MEMORYINTERFACE_H

#include <QString>
#include <QVector>
#include "QueryResult.h"
#include <QDebug>

class MemoryInterface{
    public:
        enum Type{
            DATA_ONLY = 0, INSTRUCTION_ONLY = 1, BOTH =2
        };
        //to observe from outside
        int id;
        Type type;
        int indexBits;
        int logDataWordCount;
        int logAssociativity;
        double delay;
        MemoryInterface *next = NULL;

        MemoryInterface(){
        }

        virtual QueryResult *read(unsigned int address, unsigned int length)=0;
        virtual QueryResult *read(unsigned int address)=0;
        virtual double write(QVector<Value> *value, unsigned int address)=0;
        virtual double write(Value value, unsigned int address)=0;

        virtual QByteArray save()=0;
        virtual void restore(QByteArray state)=0;

        double write(QVector<int> *value, unsigned int address);
        double write(int value, unsigned int address);
        double write(QVector<float> *value, unsigned int address);
        double write(float value, unsigned int address);

        virtual void init()=0;
};

class DummyMem: public MemoryInterface{
    public:
        DummyMem(MemoryInterface::Type type, int indexBits, int logDataWordCount, int logAssociativity, double delay){
            this->type = type;
            this->indexBits = indexBits;
            this->logDataWordCount = logDataWordCount;
            this->logAssociativity = logAssociativity;
            this->delay = delay;
        }


        QueryResult *read(unsigned int address, unsigned int length){
            (void) address; // Just to stop -Wall from complaining
            (void) length;
            qDebug() << "dummy dum dum dum";
            exit(-1);
        }
        QueryResult *read(unsigned int address){
            (void) address; // Just to stop -Wall from complaining
            qDebug() << "dummy dum dum dum";
            exit(-1);
        }
        double write(QVector<Value> *value, unsigned int address){
            (void) address; // Just to stop -Wall from complaining
            (void) value;
            qDebug() << "dummy dum dum dum";
            exit(-1);
        }
        double write(Value value, unsigned int address){
            (void) address; // Just to stop -Wall from complaining
            (void) value;
            qDebug() << "dummy dum dum dum";
            exit(-1);
        }

        QByteArray save(){
            qDebug() << "dummy dum dum dum";
            exit(-1);
        }
        void restore(QByteArray state){
            (void) state; // Just to stop -Wall from complaining
            qDebug() << "dummy dum dum dum";
            exit(-1);
        }

        void init(){
            qDebug() << "dummy dum dum dum";
            exit(-1);
        }

};
#endif
