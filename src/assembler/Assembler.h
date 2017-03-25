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
#include <QDir>
#include <QFile>
#include "Problem.h"
#include "../computer/Architecture.h"
#include "InstructionResolver.h"
#include "ConditionResolver.h"



/* This class will contain the result of compilation
 * If isAssembled is true, then errorList will point to NULL 
 * If isAssembled is false, then assembly will point to NULL
 */
class Assembled{
  public:
      ~Assembled(){
          delete instructions;
          delete problemLog;
      }
    QString fileName;
    bool isAssembled; 
    int elaspedTime;

    QVector<uint>* instructions;
    QList<Problem>* problemLog;
};
Q_DECLARE_METATYPE(Assembled);


class Preprocessed{
  public:
      QString fileName;
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
        bool useWall = true;
};
Q_DECLARE_METATYPE(AssemblerConfiguration);

#define HEADER_BUFFER 32u
/* Assembler is a singleton object.
 * 
 *
 */

class Assembler: public QObject{
    Q_OBJECT
  public: 
    //Constructor
    Assembler();
    ~Assembler();

    //Fields
    bool _success;
    uint mainAddress = INSTRUCTION_SIZE;

    const InstructionResolver IRS;
    const ConditionResolver CRS;

    //Symbol table related
    QMap<QString, QString>* _labelTable = NULL;
    QMap<QString, QString>* _aliasTable = NULL;
    QMap<QString, QStringList>* _macroTable = NULL;

    //Log purpose
    QList<Problem>* _problemLog;

    //Data processing related
    QList<Preprocessed>* _preprocessedQueue = NULL;
    QVector<uint>* _instructions = NULL;
    
    //Configuration
    AssemblerConfiguration _config;

public slots:
    void assemble(QString fileName, AssemblerConfiguration config, bool runAfter);

signals:
void resultReady(Assembled* assembled, bool runAfter);

  private:

    //Initialize variables
    void init();
    void clear();
    void throwWarning(QString fileName, int lineNumber, int wordNumber, QString cause);
    void throwError(QString fileName, int lineNumber, int wordNumber, QString cause);

    void processFile(QString fileName);

    //Sort the documents, if order is true
    void sortDocuments(QStringList documents);

    void preprocessDocument(QStringList lines, QString fileName);
    void preprocessLine(QString fileName, int lineNumber, QString line);
    void processLines();
    void processLine(Preprocessed preprocessed);
    void immiMacro(QString front, uint immi, QString end, uint nextAddress);
    void writeHeader();

};

#endif
