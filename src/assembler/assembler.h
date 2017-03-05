#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "assembly.h"
#include "../instruction/conditionResolver.h"
#include <QVector>
#include <QQueue>
#include <QMap>
#include "../instruction/instructionResolver.h"

/* Contain error generated during assembly
*/
class Error{
  public:
    int docNumber;
    int lineNumber;
    int wordNumber;
    QString cause;
    Error(int docNumber, int lineNumber, int wordNumber, QString cause){
      docNumber = docNumber;
      lineNumber = lineNumber;
      wordNumber = wordNumber;
      cause = cause;
    }
};

class Warning{
  public:
    int docNumber;
    int lineNumber;
    int wordNumber;
    QString cause;
    Warning(int docNumber, int lineNumber, int wordNumber, QString cause){
      docNumber = docNumber;
      lineNumber = lineNumber;
      wordNumber = wordNumber;
      cause = cause;
    }
};


/* This class will contain the result of compilation
 * If isAssembled is true, then errorList will point to NULL 
 * If isAssembled is false, then assembly will point to NULL
 */
class Assembled{
  public:
    bool isAssembled; 
    int elaspedTime;
    Assembly* assembly;
    QList<Error>* errorLog;
    QList<Warning>* warningLog;

};


class Preprocessed{
  public:
    int docNumber; //nth document
    int lineNumber; //nth line

    int address;
    QStringList tokens;
};

class SymbolTable{
  public:
    QMap<QString, uint>* labelMap;
};

/* Assembler is a singleton object.
 * 
 *
 */
class Assembler{
  public: 
    //Constructor
    Assembler();
    ~Assembler();

    //Fields
    bool _success;
    uint mainAddress;

    const InstructionResolver IRS;
    const ConditionResolver CRS;

    //Symbol table related
    QMap<QString, uint>* _labelTable;
    QMap<QString, QString>* _aliasTable;

    //Log purpose
    QList<Error>* _errorLog;
    QList<Warning>* _warningLog;

    //Data processing related
    QList<Preprocessed>* _preprocessedQueue;
    QVector<uint>* _instructions;
    QVector<uint>* _addresses;

    Assembled* assemble(QStringList document);

  private:
    static bool isExisting;

    //Initialize variables
    void init();
    void loadGlobalAlias();
    void clear();
    void throwWarning(int docNumber, int lineNumber, int wordNumber, QString cause);
    void throwError(int docNumber, int lineNumber, int wordNumber, QString cause);

    void preprocessLines(QStringList documents);
    void preprocessLine(int docNumber, int lineNumber, QString line);
    void processLines();
    void processLine(Preprocessed preprocessed);

};

#endif
