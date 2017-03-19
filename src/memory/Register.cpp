#include "Register.h"
#include <QDebug>

Register::Register(){
    Value intZero = {0};
    Value floatZero;
    floatZero.f = 0;

    _iScas.fill(intZero, NUMBER_OF_INTEGER_SCALAR_REGISTER);
    _fScas.fill(floatZero, NUMBER_OF_FLOAT_SCALAR_REGISTER);
    _sRegs.fill(intZero, NUMBER_OF_SYSTEM_REGISTER);

    for(int i = 0; i < NUMBER_OF_INTEGER_VECTOR; i++){
        QVector<Value> vec;
        vec.fill(intZero,VECTOR_SIZE);
        _iVecs.append(vec);
    }

    for(int i = 0; i < NUMBER_OF_FLOAT_VECTOR; i++){
        QVector<Value> vec;
        vec.fill(floatZero,VECTOR_SIZE);
        _fVecs.append(vec);
    }
}


Register::~Register(){
    //Do nothing
}

QueryResult* Register::read(unsigned int address, unsigned int length){
    if(address < NUMBER_OF_INTEGER_SCALAR_REGISTER + NUMBER_OF_FLOAT_SCALAR_REGISTER +NUMBER_OF_SYSTEM_REGISTER|| address >= TOTAL_NUMBER_OF_REGISTERS){
        qDebug()<< "Invalid Access: address has to be between 24 to 31" << endl;
        exit(-1);
    }
    if(length != VECTOR_SIZE){
        qDebug() << "Invalid Access: length has to be 64" << endl;
        exit(-1);
    }

    address -= NUMBER_OF_INTEGER_SCALAR_REGISTER + NUMBER_OF_FLOAT_SCALAR_REGISTER +NUMBER_OF_SYSTEM_REGISTER;
    if(address < NUMBER_OF_INTEGER_VECTOR){
        return new QueryResult(_iVecs[address], delay);
    }
    else{
        return new QueryResult(_fVecs[address - NUMBER_OF_INTEGER_VECTOR], delay);
    }
}

QueryResult* Register::read(unsigned int address){
    if(address < NUMBER_OF_INTEGER_SCALAR_REGISTER){
        QVector<Value> vec;
        vec.push_back(_iScas[address]);
        return new QueryResult(vec, delay);
    }
    else if(address < NUMBER_OF_INTEGER_SCALAR_REGISTER + NUMBER_OF_FLOAT_SCALAR_REGISTER){
        QVector<Value> vec;
        vec.push_back(_fScas[address-NUMBER_OF_INTEGER_SCALAR_REGISTER]);
        return new QueryResult(vec, delay);

    }
    else if(address <  NUMBER_OF_INTEGER_SCALAR_REGISTER + NUMBER_OF_FLOAT_SCALAR_REGISTER + NUMBER_OF_SYSTEM_REGISTER){
        QVector<Value> vec;
        vec.push_back(_sRegs[address-NUMBER_OF_INTEGER_SCALAR_REGISTER- NUMBER_OF_FLOAT_SCALAR_REGISTER]);
        return new QueryResult(vec, delay);
    }
    qDebug() << "Register address " << address << " does not exist!";
    exit(-1);
}


double Register::write(QVector<Value> *value, unsigned int address){
    if(address < NUMBER_OF_INTEGER_SCALAR_REGISTER + NUMBER_OF_FLOAT_SCALAR_REGISTER +NUMBER_OF_SYSTEM_REGISTER|| address >= TOTAL_NUMBER_OF_REGISTERS){
        qDebug()<< "Invalid Access: address has to be between 24 to 31" << endl;
        exit(-1);
    }
    if(value->size() != VECTOR_SIZE){
        qDebug() << "Invalid Access: length has to be 64" << endl;
        exit(-1);
    }

    address -= NUMBER_OF_INTEGER_SCALAR_REGISTER + NUMBER_OF_FLOAT_SCALAR_REGISTER +NUMBER_OF_SYSTEM_REGISTER;
    if(address < NUMBER_OF_INTEGER_VECTOR){
        for(int i = 0; i < VECTOR_SIZE;i++){
        _iVecs[address].replace(i,value->at(i));
        }
    }
    else{
        for(int i = 0; i < VECTOR_SIZE;i++){
        _fVecs[address-NUMBER_OF_INTEGER_VECTOR].replace(i,value->at(i));
        }
    }
    return delay;
}


double Register::write(Value input, unsigned int address){
    if(address < NUMBER_OF_INTEGER_SCALAR_REGISTER) {
        _iScas.replace(address,input);
        return delay;
    }
    address -= NUMBER_OF_INTEGER_SCALAR_REGISTER;

    if(address < NUMBER_OF_FLOAT_SCALAR_REGISTER) {
        _fScas.replace(address,input);
        return delay;
    }
    address -= NUMBER_OF_FLOAT_SCALAR_REGISTER;

    if(address < NUMBER_OF_SYSTEM_REGISTER) {
        _sRegs.replace(address,input);
        return delay;
    }
    qDebug()<< "Invalid Access: address has to be between 0 to " << (NUMBER_OF_INTEGER_SCALAR_REGISTER+NUMBER_OF_FLOAT_SCALAR_REGISTER+NUMBER_OF_SYSTEM_REGISTER) << endl;
    exit(-1);
}

QString *Register::save(){
  return new QString("");
}

void Register::restore(QString *state){
  qDebug() << state << endl;
}
