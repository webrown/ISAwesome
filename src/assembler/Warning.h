#ifndef WARNING_H
#define WARNING_H 
#include <QString>
#include <QDebug>

class Warning{
    public:
        int docNumber;
        int lineNumber;
        int wordNumber;
        QString cause;
        Warning(QString cause, int docNumber, int lineNumber, int wordNumber){
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

