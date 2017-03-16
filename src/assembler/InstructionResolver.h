#ifndef INSTRUCTIONRESOLVER_H
#define INSTRUCTIONRESOLVER_H
#include <QMap>
#include <QVector>
#include "../utility.h"
#include "../assembler/Error.h"
#include "../assembler/Warning.h"

class ParseResult{
    public:
        uint parsed;
        QString unparsed;
        int failureLocation = -1;
        QString error = "None";
        QString warning = "None";
};

class InstructionDefinition{
    public:
        QString name;
        uint opcode;
        ParseResult (*parse)(QStringList);
        ParseResult (*unparse)(uint);

        InstructionDefinition(QString name, uint opcode,ParseResult (*parseFunc)(QStringList), ParseResult (*unparseFunc)(uint) ){
            this->name = name;
            this->opcode = opcode;
            this->parse = parseFunc;
            this->unparse = unparseFunc;
        }
};

class InstructionResolver{
    public:
        QMap<QString, InstructionDefinition*> nameTable;
        QMap<uint, InstructionDefinition*> opcodeTable;
        //    const QTable<uint, Instruction> instructionTable;
       
        InstructionResolver();
        ~InstructionResolver();
        void set(QString name, uint opcode, ParseResult (*parseFunc)(QStringList), ParseResult (*unparseFunc)(uint));



        

};
#endif
