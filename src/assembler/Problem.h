#ifndef PROBLEM_H
#define PROBLEM_H 
#include <QString>
#include <QDebug>

enum ProblemType{
    WARNING, ERROR
};
/* Contain error generated during assembly
*/
class Problem{
    public:
        ProblemType type;
        int lineNumber;
        int wordNumber;
        QString cause, fileName;

        //If wordNumber = -1, then whole line has problem
        Problem(ProblemType type, QString cause, QString fileName, int lineNumber, int wordNumber = -1){
            this->type = type;
            this->fileName = fileName;
            this->lineNumber = lineNumber;
            this->wordNumber = wordNumber;
            this->cause = cause;
            qDebug() << (type==WARNING ? "Warning" : (type == ERROR ? "Error" : "???"));
            qDebug() << "File Name: " << fileName;
            qDebug() << "Line Number: " << lineNumber << " \tWord Number: " << wordNumber;
            qDebug() << "cause:" << cause;
        }

};
#endif

