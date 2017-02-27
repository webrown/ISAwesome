#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <QString>

enum OperandType{
    REG, VEC, IMM16, UNDEFINED
};

class Instruction {
    public:
        virtual uint getOpcode() =0;
        virtual uint parseOperands(QStringList ops, QString* meesage) = 0;

        virtual QString getName()=0;
        virtual QStringList unparseOperands(uint ops, QString* message)=0;

        virtual void operate(uint ops)=0;
    protected:
        bool checkOpNum(int num, QStringList ops, QString* m);
        uint convertOperand(QString ops, QString* m,OperandType* type);
};
#endif
