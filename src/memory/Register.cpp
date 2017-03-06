#include "Register.h"
#include <QDebug>

Register::Register(){
    _iScas.fill(0,NUMBER_OF_INTEGER_SCALAR_REGISTER);
    _fScas.fill(0,NUMBER_OF_FLOAT_SCALAR_REGISTER);

    for(int i = 0; i < NUMBER_OF_INTEGER_VECTOR; i++){
        QVector<int> vec;
        vec.fill(0,VECTOR_SIZE);
        _iVecs.append(vec);
    }

    for(int i = 0; i < NUMBER_OF_FLOAT_VECTOR; i++){
        QVector<float> vec;
        vec.fill(0,VECTOR_SIZE);
        _fVecs.append(vec);
    }
    qDebug() << "Registers generated" << endl;
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
        QVector<int> vec;
        vec[0] = _iScas[address];
        return new QueryResult(vec, delay);
    }
    else if(address < NUMBER_OF_INTEGER_SCALAR_REGISTER + NUMBER_OF_FLOAT_SCALAR_REGISTER){
        QVector<float> vec;
        vec[0] = _fScas[address-NUMBER_OF_INTEGER_SCALAR_REGISTER];
        return new QueryResult(vec, delay);

    }
    else if(address <  NUMBER_OF_INTEGER_SCALAR_REGISTER + NUMBER_OF_FLOAT_SCALAR_REGISTER + NUMBER_OF_SYSTEM_REGISTER){
        QVector<int> vec;
        vec[0] = _fScas[address-NUMBER_OF_INTEGER_SCALAR_REGISTER- NUMBER_OF_FLOAT_SCALAR_REGISTER];
        return new QueryResult(vec, delay);
    }
}


double Register::write(QVector<int> *value, unsigned int address){
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
        _iVecs[address].replace(0,value->at(i));
        }
    }
    else{
        for(int i = 0; i < VECTOR_SIZE;i++){
        _fVecs[address-NUMBER_OF_INTEGER_VECTOR].replace(0,value->at(i));
        }
    }
}

