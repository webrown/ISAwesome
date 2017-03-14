#ifndef ASSEMBLER_H
#define ASSEMBLER_H 
#include <climits>
#include <iostream>
#include <QVector> 
#include <QtDebug>
#include <QTime>
#include <QVector>
#include <QQueue>
#include <QMap>
#include <QFile>
#include "Error.h"
#include "Warning.h"
#include "../architecture.h"
#include "../instruction/InstructionResolver.h"
#include "../instruction/conditionResolver.h"



/* This class will contain the result of compilation
 * If isAssembled is true, then errorList will point to NULL 
 * If isAssembled is false, then assembly will point to NULL
 */
class Assembled{
  public:
    bool isAssembled; 
    int elaspedTime;

    QVector<uint>* instructions;
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

class AssemblerConfiguration{
    public:
        bool useDefaultMacro = true;
        bool useGlobalMacro = true;
        bool useDefaultAlias = true;
        bool useGlobalAlias = true;
        bool useMainEntry = true;
        bool useOrder = true;
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
    QMap<QString, QStringList>* _macroTable;

    //Log purpose
    QList<Error>* _errorLog;
    QList<Warning>* _warningLog;

    //Data processing related
    QList<Preprocessed>* _preprocessedQueue;
    QVector<uint>* _instructions;
    QVector<uint>* _addresses;
    
    //Configuration
    AssemblerConfiguration _config;


    Assembled* assemble(QStringList documents, AssemblerConfiguration config);

  private:
    static bool isExisting;

    //Initialize variables
    void init();
    void clear();
    void throwWarning(int docNumber, int lineNumber, int wordNumber, QString cause);
    void throwError(int docNumber, int lineNumber, int wordNumber, QString cause);

    void loadFromSystemFile(QString fileName);

    //Sort the documents, if order is true
    void sortDocuments(QStringList documents);

    void preprocessLines(QStringList documents);
    void preprocessLine(int docNumber, int lineNumber, QString line);
    void processLines();
    void processLine(Preprocessed preprocessed);
    uint convertRegister(QString str);

};

#endif
