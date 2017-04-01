#ifndef PROGRAMMANAGERY_H
#define PROGRAMMANAGERY_H
#include "Computer.h"
#include <QDataStream>
#include "../assembler/ProgramManagerX.h"

namespace ProgramManagerY{
    bool save(Computer* computer, QString fileName){

        QByteArray regData = computer->regs->save();
        QByteArray memData = computer->mems->_mainMemory->save();


        // QByteArray regData = qCompress(computer->regs->save(),9);
        // QByteArray memData = qCompress(computer->mems->_mainMemory->save(), 9);

        QFile file(fileName);
        //file can't be open return false
        if(file.open(QIODevice::WriteOnly | QIODevice::Text) == false){
            return false;
        }
        QDataStream out(&file);


        //If change, change program x
        //Dirty hack to fix instruciton address error
        out << (qint32)(computer->program->instructionEndAddress);
        out << (qint32)computer->program->dataEndAddress;
        out << (qint32)computer->program->size;

        QVector<uint>* instructions = computer->program->instructions;
        for(uint i = 0; i < computer->program->size; i++){
            out << (qint32)instructions->at(i);
        }

        out << (qint32)1;
        out << (qint32)0; //fix this 
        out << (qint32)1;

        out << (qint32)regData.size();
        for(qint8 byte: regData){
            out << byte;
        }

        out << (qint32)memData.size();
        for(qint8 byte: memData){
            out << byte;
        }

        file.close();
        return true;
    }
    bool restore(Computer* computer, QString fileName){
        QFile file(fileName);
        //file can't be open return false
        if(file.open(QIODevice::ReadOnly ) == false){
            qDebug() << "Restore failed, file not found";

            return false;
        }
        QDataStream in(&file);
        qint32 line;

        //If change, chnage program X
        computer->program  = new Program();

        in >> (computer->program->instructionEndAddress);
        in >> (computer->program->dataEndAddress);
        in >> (computer->program->size); 

        computer->program->instructions = new QVector<uint>();
        for(int i =0; i < computer->program->size; i++){
            quint32 a;
            in  >> a;
            qDebug() << QString::number(a,2);
            computer->program->instructions->append(a);
        }

        in >> line;
        int nReg = line;
        in >> line;
        int nCache = line;

        in >> line;
        int nMem = line;

        //start to read register
        in >> line;
        int lReg = line;

        QByteArray tmp;
        for(int i =0; i < lReg; i++){
            qint8 x;
            in >> x;
            tmp.append(x);
        }

        // QByteArray regData = qUncompress(tmp);
        QByteArray regData = tmp;


        //TODO cache...
    
        //start to read register
        in >> line;
        int lMem = line;

        QByteArray tmp2;
        for(int i =0; i < lMem; i++){
            qint8 x;
            in >> x;
            tmp2.append(x);
        }
        // QByteArray memData = qUncompress(tmp2);
        QByteArray memData = tmp2;
        // qDebug() << memData;
        //Start to load up the data
        computer->regs->restore(regData);
        computer->mems->_mainMemory->restore(memData);

        return true;
    }
};
#endif

