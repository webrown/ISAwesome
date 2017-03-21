#ifndef WARNING_H
#define WARNING_H 
#include <QString>
#include <QDebug>

class Warning{
    public:
        int lineNumber;
        int wordNumber;
        QString cause, fileName;
        Warning(QString cause, QString fileName, int lineNumber, int wordNumber){
            fileName = fileName;
            lineNumber = lineNumber;
            wordNumber = wordNumber;
            cause = cause;
            qDebug() << "File Name: " << fileName;
            qDebug() << "Line Number: " << lineNumber << " \tWord Number: " << wordNumber;
            qDebug() << "cause:" << cause;
        }
};
#endif

