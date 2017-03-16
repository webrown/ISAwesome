#ifndef ERROR_H
#define ERROR_H 
#include <QString>
#include <QDebug>

/* Contain error generated during assembly
*/
class Error{
    public:
        int lineNumber;
        int wordNumber;
        QString cause, fileName;

        //If wordNumber = -1, then whole line has problem
        Error(QString cause, QString fileName, int lineNumber, int wordNumber = -1){
            this->fileName = fileName;
            this->lineNumber = lineNumber;
            this->wordNumber = wordNumber;
            this->cause = cause;
            qDebug() << "File Name: " << fileName;
            qDebug() << "Line Number: " << lineNumber << " \tWord Number: " << wordNumber;
            qDebug() << "cause:" << cause;

        }

};
#endif

