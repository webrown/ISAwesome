#ifndef PROGRAMMANAGERX_H
#define PROGRAMMANAGERX_H
#include <QVector>
#include <QFile>
#include <QDataStream>
#include <QDebug>
#include "Assembler.h"
class ProgramManagerX{
    public:
    static void saveProgram(QString fileName, Program* program){
        qDebug() << "SAVE: " <<fileName;
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
            qDebug() << "PROGRAM SAVE FAILED";
            return;
        }


        QDataStream out(&file);

        out << (qint32)program->instructionEndAddress;
        out << (qint32)program->dataEndAddress;
        // qDebug() << program->size;
        out << (qint32)program->size;

        QVector<uint>* instructions = program->instructions;
        for(uint i = 0; i < program->size; i++){
            out << (qint32)instructions->at(i);
        }
    }

    static Program* loadProgram(QString fileName){
        qDebug() << "LOAD: " << fileName;
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)){
            qDebug() << "PROGRAM LOAD FAILED";
            return NULL;
        }

        Program* program  = new Program();
        QDataStream in(&file);

        in >> (program->instructionEndAddress);
        in >> (program->dataEndAddress);
        in >> (program->size); 

        program->instructions = new QVector<uint>();
        for(uint i =0; i < program->size; i++){
            qint32 a;
            in  >> a;
            program->instructions->append(a);
        }
        // qDebug() << "LOAD: FINSIH";
        // qDebug() << QString::number(program->instructionEndAddress).rightJustified(32,'0');
        // qDebug() << QString::number(program->dataEndAddress).rightJustified(32,'0');
        // qDebug() << QString::number(program->size).rightJustified(32,'0');


        return program;
    }

};
#endif
