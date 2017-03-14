#ifndef ERROR_H
#define ERROR_H 
#include <QString>
#include <QDebug>

/* Contain error generated during assembly
*/
class Error{
    public:
        int docNumber;
        int lineNumber;
        int wordNumber;
        QString cause;

        //If wordNumber = -1, then whole line has problem
        Error(QString cause, int docNumber, int lineNumber, int wordNumber = -1){
            docNumber = docNumber;
            lineNumber = lineNumber;
            wordNumber = wordNumber;
            cause = cause;
            qDebug() << "Document Number: " << docNumber << endl;
            qDebug() << "Line Number: " << lineNumber << " \tWord Number: " << wordNumber << endl;
            qDebug() << "cause:\n" << cause <<endl;
        }

};
#endif

