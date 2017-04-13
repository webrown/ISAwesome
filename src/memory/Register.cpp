#include "Register.h"
#include <QDebug>
#include "serialization.h"
#include "Flag.h"

Register::Register(){
    init();
}

Register::~Register(){
    //Do nothing
}
void Register::init(){
    qDebug() << "COM: reseting Register";
    Value intZero = {0};
    Value floatZero;
    floatZero.f = 0;

    _flag = intZero;
    _flags.fill(intZero, VECTOR_SIZE);
    _scas.fill(intZero, NUMBER_OF_SCALAR_REGISTER);
    for(int i =0; i < NUMBER_OF_VECTOR_REGISTER; i++){
        QVector<Value> vec;
        vec.fill(floatZero,VECTOR_SIZE);
        _vecs.append(vec);
    }
    
    // Always bit should be set (and in theory never unset)
    using namespace Flag;
    _flag  = add(_flag,  AL);
    _flags = add(_flags, AL);
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
    Q_ASSERT(0<= i &&i < NUMBER_OF_SCALAR_REGISTER);
    return _scas[i];
}

Value Register::read(Value i){
    return read(i.i);
}

void Register::write(Value v, int i){
    Q_ASSERT(0<= i &&i < NUMBER_OF_SCALAR_REGISTER);
    _scas[i] = v;
}

void Register::write(int v, int address) {
    Value value;
    value.i = v;
    write(value, address);
}

void Register::write(unsigned int v, int address) {
    Value value;
    value.asUInt = v;
    write(value, address);
}

void Register::write(float v, int address) {
    Value value;
    value.f = v;
    write(value, address);
}

QVector<Value> Register::readVector(Value i){
    return readVector(i.i);
}

QVector<Value> Register::readVector(int i){
    Q_ASSERT(NUMBER_OF_SCALAR_REGISTER <= i && i <NUMBER_OF_SCALAR_REGISTER + NUMBER_OF_VECTOR_REGISTER);
    return _vecs[i-NUMBER_OF_SCALAR_REGISTER];
}

void Register::writeVector(QVector<Value> v, int i){
    Q_ASSERT(NUMBER_OF_SCALAR_REGISTER <= i && i <NUMBER_OF_SCALAR_REGISTER + NUMBER_OF_VECTOR_REGISTER);
    qDebug() << v.size();
    Q_ASSERT(v.size() == VECTOR_SIZE);
    _vecs[i-NUMBER_OF_SCALAR_REGISTER] = v;
}

void Register::writeVector(QVector<int> v, int address) {
    QVector<Value> values;
    for(int i = 0; i < v.size(); i++) {
        Value value;
        value.i = v.at(i);
        values.push_back(value);
    }
    writeVector(values, address);
}

void Register::writeVector(QVector<float> v, int address) {
    QVector<Value> values;
    for(int i = 0; i < v.size(); i++) {
        Value value;
        value.f = v.at(i);
        values.push_back(value);
    }
    writeVector(values, address);
    
}

void Register::write(QVector<Value> v, int address) {
    writeVector(v, address);
}

void Register::write(QVector<int> v, int address) {
    writeVector(v, address);
}

void Register::write(QVector<float> v, int address) {
    writeVector(v, address);
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

QByteArray Register::save(){
    QVector<int> result;
    QByteArray ret;

    result += _flag.i;
    for(int i = 0; i < _scas.size(); i++) {
        result += _scas.at(i).i;
    }
    for(int i = 0; i < _flags.size(); i++) {
        result += _flags.at(i).i;
    }
    for(int i = 0; i < _vecs.size(); i++) {
        for(int j = 0; j < _vecs.at(i).size(); j++) {
            result += _vecs.at(i).at(j).i;
        }
    }
    serialize(&ret, &result);
    return ret;
}

void Register::restore(QByteArray state){
    QVector<int> stateVector; 
    deserialize(&state, &stateVector);
    int vectorBoundary = 1+_scas.size()+_flags.size();
    for(int i = 0; i < stateVector.size(); i++) {
        if(i < 1) {
            _flag.i = stateVector.at(i);
            continue;
        }
        if(i < 1+_scas.size()) {
           _scas[i-1].i = stateVector.at(i); 
           continue;
        }
        if(i < vectorBoundary) {
           _flags[i-(1+_scas.size())].i = stateVector.at(i); 
           continue;
        }
        if(i < vectorBoundary+_vecs.size()*VECTOR_SIZE) {
           _vecs[(i-vectorBoundary)/VECTOR_SIZE][(i-vectorBoundary)%VECTOR_SIZE].i = stateVector.at(i); 
           continue;
        }
    }
}

bool Register::isVectorIndex(int index){
    return index >= (int)vectorIntegers;
}

bool Register::isFloatIndex(int index){
    return (index >= (int)scalarFloats && index < (int)specials) || (index >= (int)vectorFloats);
}

bool Register::indexExists(int index){
    return (index < TOTAL_NUMBER_OF_REGISTERS);
}

bool Register::isScalarIndex(int index){
    return !isVectorIndex(index);
}

bool Register::isIntIndex(int index){
    return !isFloatIndex(index);
}

bool Register::isVectorIndex(Value index){
    return isVectorIndex(index.i);
}

bool Register::isFloatIndex(Value index){
    return isFloatIndex(index.i);
}

bool Register::indexExists(Value index){
    return indexExists(index.i);
}

bool Register::isScalarIndex(Value index){
    return isScalarIndex(index.i);
}

bool Register::isIntIndex(Value index){
    return isIntIndex(index.i);
}
