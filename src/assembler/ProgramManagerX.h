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
        for(int i = 0; i < instructions->size(); i++){
            out << (qint32)instructions->at(i);
        }
    }

    static QVector<uint>* loadProgram(QString fileName){
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return NULL;

        QVector<uint>* instructions = new QVector<uint>();
        QDataStream in(&file);
        QString str;
        qint32 size;
        in >> size; 
        qDebug() << size;
        for(int i =0; i < size; i++){
            qint32 a;
            in  >> a;
            instructions->append(a);
        }

        return instructions;
    }

};
#endif
