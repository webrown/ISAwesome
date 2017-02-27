#ifndef ASSEMBLED_H
#define ASSEMBLED_H

#include "assembly.h"
#include <QList>

/* Contain error generated during assembly
 */
class Error{
    public:
        int lineNumber;
        int wordNumber;
        QString cause;
};
class Warning{
    public:
        int lineNumber;
        int wordNumber;
        QString cause;
};


/* This class will contain the result of compilation
 * If isAssembled is true, then errorList will point to NULL 
 * If isAssembled is false, then assembly will point to NULL
 */
class Assembled{
  public:
    bool isAssembled; 
    Assembly* assembly;

    QList<Error>* errorList;
    QList<Warning>* warningList;
      
};
#endif
