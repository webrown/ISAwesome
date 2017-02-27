#include "instruction.h"
#include <QStringList>
#include <QRegExp>

bool Instruction::checkOpNum(int n, QStringList ops, QString*m){
    if(ops.size() == n){
        return true;
    }
    m = new QString("Invalid Argument: " + QString(n) + " arguments was needed. " + ops.size() + " arguments are found");
    return false;
}

uint converOperand(QString op, QString* m, OperandType* type){
    //register

    QRegExp nReg("^R([0-9]*)$");
    QRegExp sReg("^(SP|PC|BP|LR)$");
    QRegExp vec("^V([0-9]*)$");
    QRegExp hex("#0X[0-9]*)$");
    QRegExp bin("#0B[0-9]*)$");
    QRegExp dec("#0D[0-9]*)$");
    

    if(nReg.exactMatch(op)){
        QString numS = op.right(op.length()-1);

    }
    if(sReg.exactMatch(op)){
    }
    if(vec.exactMatch(op)){
    }
    if(hex.exactMatch(op)){
    }
    if(bin.exactMatch(op)){
    }
    if(dec.exactMatch(op)){
     
    }
    else{
        m = new QString("Invalid Argument: " + op + " is not a valid argument");
        return false;
    }
}
