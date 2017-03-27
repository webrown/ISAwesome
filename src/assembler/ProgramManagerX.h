#ifndef PROGRAMMANAGERX_H
#define PROGRAMMANAGERX_H
#include <QVector>
#include <QFile>
#include <QDataStream>
#include <QDebug>
class ProgramManagerX{
    public:
    static void saveProgram(QString fileName, QVector<uint>* instructions){
        qDebug() << "SAVE: " <<fileName;
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;

        QDataStream out(&file);
        out << (qint32)instructions->size();
        qDebug() << "SIZE: " << instructions->size();
        for(int i = 0; i < instructions->size(); i++){
            out << (qint32)instructions->at(i);
        }
    }

    static QList<uint> loadProgram(QString fileName){
        qDebug() << "LOAD: " << fileName;
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)){
            return QList<uint>();
        }

        QList<uint> instructions;
        QDataStream in(&file);
        QString str;
        qint32 size;
        in >> size; 
        // qDebug() <<"SIZE: " << size;
        for(int i =0; i < size; i++){
            qint32 a;
            in  >> a;
            instructions.append(a);
        }

        return instructions;
    }

};
#endif
