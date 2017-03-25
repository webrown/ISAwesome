#include "Register.h"
#include <QDebug>
#include "serialization.h"

Register::Register(){
    Value intZero = {0};
    Value floatZero;
    floatZero.f = 0;

    _flag = intZero;
    _flags.fill(intZero, VECTOR_SIZE);
    _scas.fill(intZero, NUMBER_OF_FLOAT_SCALAR_REGISTER+ NUMBER_OF_INTEGER_SCALAR_REGISTER +NUMBER_OF_SYSTEM_REGISTER);
    for(int i =0; i < NUMBER_OF_FLOAT_SCALAR_REGISTER+ NUMBER_OF_INTEGER_SCALAR_REGISTER; i++){
        QVector<Value> vec;
        vec.fill(floatZero,VECTOR_SIZE);
        _vecs.append(vec);
    }

    //----------------Deprecated--------------------
    _iScas.fill(intZero, NUMBER_OF_INTEGER_SCALAR_REGISTER);
    _fScas.fill(floatZero, NUMBER_OF_FLOAT_SCALAR_REGISTER);
    _sRegs.fill(intZero, NUMBER_OF_SYSTEM_REGISTER);
    _flagVec.fill(intZero, VECTOR_SIZE);

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

uint Register::getPC(){
    return _scas[PC].asUInt;
}

uint Register::getSP(){
    return _scas[SP].asUInt;
}
uint Register::getBP(){
    return _scas[BP].asUInt;
}
uint Register::getLR(){
    return _scas[LR].asUInt;
}

Value Register::read(int i){
    Q_ASSERT(0<= i &&i > NUMBER_OF_SCALAR_REGISTER);
    return _scas[i];
}

void Register::write(int i, Value v){
    Q_ASSERT(0<= i &&i > NUMBER_OF_SCALAR_REGISTER);
    _scas[i] = v;
}

QVector<Value> Register::readVector(int i){
    Q_ASSERT(NUMBER_OF_SCALAR_REGISTER <= i && i <NUMBER_OF_SCALAR_REGISTER + NUMBER_OF_VECTOR_REGISTER);
    return _vecs[i];
}

void Register::writeVector(int i, QVector<Value> v){
    Q_ASSERT(NUMBER_OF_SCALAR_REGISTER <= i && i <NUMBER_OF_SCALAR_REGISTER + NUMBER_OF_VECTOR_REGISTER);
    Q_ASSERT(v.size() == VECTOR_SIZE);
    _vecs[i] = v;
}

Value Register::readFlag(){
    return _flag;
}

void Register::writeFlag(Value v){
    _flag = v;
}

QVector<Value> Register::readFlags(){
    return _flags;
}

void Register::writeFlags(QVector<Value> v){
    Q_ASSERT(v.size() == VECTOR_SIZE);
    _flags = v;
}












//--------------------Deprecated---------------------
QueryResult* Register::read(unsigned int address, unsigned int length){
    if(address < NUMBER_OF_INTEGER_SCALAR_REGISTER + NUMBER_OF_FLOAT_SCALAR_REGISTER +NUMBER_OF_SYSTEM_REGISTER|| address >= TOTAL_NUMBER_OF_REGISTERS+1){
        qDebug()<< "Invalid Access: address has to be between " << (NUMBER_OF_INTEGER_SCALAR_REGISTER + NUMBER_OF_FLOAT_SCALAR_REGISTER +NUMBER_OF_SYSTEM_REGISTER) << " to " << (TOTAL_NUMBER_OF_REGISTERS+1) << endl;
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
    else if(address < NUMBER_OF_INTEGER_VECTOR+NUMBER_OF_FLOAT_VECTOR){
        return new QueryResult(_fVecs[address - NUMBER_OF_INTEGER_VECTOR], delay);
    }
    else {
        return new QueryResult(_flagVec, delay);
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
    if(address < NUMBER_OF_INTEGER_SCALAR_REGISTER + NUMBER_OF_FLOAT_SCALAR_REGISTER +NUMBER_OF_SYSTEM_REGISTER|| address >= TOTAL_NUMBER_OF_REGISTERS+1){
        qDebug()<< "Invalid Access: address has to be between " << (NUMBER_OF_INTEGER_SCALAR_REGISTER + NUMBER_OF_FLOAT_SCALAR_REGISTER +NUMBER_OF_SYSTEM_REGISTER) << " to " << (TOTAL_NUMBER_OF_REGISTERS+1) << endl;
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
    else if(address < NUMBER_OF_INTEGER_VECTOR+NUMBER_OF_FLOAT_VECTOR){
        for(int i = 0; i < VECTOR_SIZE;i++){
            _fVecs[address-NUMBER_OF_INTEGER_VECTOR].replace(i,value->at(i));
        }
    }
    else {
        for(int i = 0; i < VECTOR_SIZE;i++){
            _flagVec.replace(i,value->at(i));
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
    QVector<int> result;
    for(int i = 0; i < _iScas.size(); i++) {
        result += _iScas.at(i).i;
    }
    for(int i = 0; i < _fScas.size(); i++) {
        result += _fScas.at(i).i;
    }
    for(int i = 0; i < _sRegs.size(); i++) {
        result += _sRegs.at(i).i;
    }
    for(int i = 0; i < _iVecs.size(); i++) {
        for(int j = 0; j < _iVecs.at(i).size(); j++) {
            result += _iVecs.at(i).at(j).i;
        }
    }
    for(int i = 0; i < _fVecs.size(); i++) {
        for(int j = 0; j < _fVecs.at(i).size(); j++) {
            result += _fVecs.at(i).at(j).i;
        }
    }
    for(int i = 0; i < _flagVec.size(); i++) {
        result += _flagVec.at(i).i;
    }
    return serialize(&result);
}

void Register::restore(QString *state){
    QVector<int> *stateVector = deserialize(state);
    unsigned int vectorBoundary = vectorIntegers+_iVecs.size()*VECTOR_SIZE;
    for(unsigned int i = 0; i < (unsigned int) stateVector->size(); i++) {
        if(i < scalarFloats) {
           _iScas[i].i = stateVector->at(i); 
           continue;
        }
        if(i < specials) {
           _fScas[i-scalarFloats].i = stateVector->at(i); 
           continue;
        }
        if(i < vectorIntegers) {
           _sRegs[i-specials].i = stateVector->at(i); 
           continue;
        }
        if(i < vectorBoundary) {
           _iVecs[(i-vectorIntegers)/VECTOR_SIZE][(i-vectorIntegers)%VECTOR_SIZE].i = stateVector->at(i); 
           continue;
        }
        if(i < vectorBoundary+_iVecs.size()*VECTOR_SIZE) {
           _fVecs[(i-vectorBoundary)/VECTOR_SIZE][(i-vectorBoundary)%VECTOR_SIZE].i = stateVector->at(i); 
           continue;
        }
        if(i < vectorBoundary+_iVecs.size()*VECTOR_SIZE + VECTOR_SIZE) {
           _flagVec[i-(vectorBoundary+_iVecs.size()*VECTOR_SIZE)].i = stateVector->at(i); 
           continue;
        }
    }
    delete stateVector;
}

