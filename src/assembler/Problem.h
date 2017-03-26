#ifndef PROBLEM_H
#define PROBLEM_H 
#include <QString>
#include <QDebug>

/* Contain error generated during assembly
*/
class Problem{

    public:
        enum ProblemType{
            WARNING, ERROR
        };
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
        }

};
#endif

