#ifndef PARSING_H
#define PARSING_H
#include <vector>
#include <QVector>
#include "MachineCode.h"
#include "assembled.h"
#include <QMultiMap>
#include <QMap>


class Preprocessed{
    public:
        int lineNumber;
        QStringList tokens;
};

class SymbolTable{
    public:
        QMap<QString, uint>* labelMap;
};

using namespace std;
void printError(Error error);

vector<int>* assemblyStringToInt(QString assemblyString);

vector<int>* parseInstructionSCondition(QString token);

bool processInstruction(QString str, QList<Error>*, Instruction* instr, QString* cond, 

bool preprocessLine(int lineNumber, QString str, QVector<uint>* addresses, QVector<Preprocessed>* preprocesseds, QList<Error>* errorLog, SymbolTable* symbolMap);
bool processLine(Preprocessed proprocessed,  QVector<uint>* instruction, QList<Error>* errorLog,SymbolTable* symbolTable);
Assembled* process(QString lines);

#endif
