#ifndef STAGEDATA_H
#define STAGEDATA_H
#include "../banana/PipelineGlobals.h"
#include "../memory/Value.h"
#include "../memory/Flag.h"
//#include "Instruction.h"
#include <QVector>
#include <QQueue>
#include <QDebug>
#include <QMap>
#include <QBitArray>

//based on https://en.wikipedia.org/wiki/Classic_RISC_pipeline
class Instruction;
class StageData{

    public:
        enum InfoStuff{
            SCALAR = 0,
            VECTOR = 4,
            SQUASHED = 1,
            NOT_SQUASHED =0,
            INTEGER = 0,
            FLOAT =8
        };
        //For all stages
        //XXXXVTDS
        //V: value type bit(Float 1, int 0)
        //S: Squash bit
        //D: dependency bit
        //T: type bit(Vector 1, Scalar 0)
        char info;

        //@@@Prefetch will fill up this field
        unsigned int instruction;

        //@@@Decode will fill up these fields
        //Conditionalflag
        Flag::FlagType condFlag;
        bool flagValue;
        QBitArray flagValues;

        //Opcode
        Opcode::Opcode opcode;
        Instruction *instructionFunctions = NULL;
        Value operand1; // Used in unary, binary, and ternary instructions
        Value operand2; // Used in binary and ternary instructions
        Value operand3; // Used in ternary instructions

        //Destination
        char destReg;
        char srcReg; // Oddly, useful for Long Operations

        //This will be 32 bit long bit array.
        unsigned int regInUse;


        Value src;
        Value dest;
        Value aux;

        QVector<Value> srcVec;
        QVector<Value> destVec;

        bool isSquashed();
        bool isVector();
        bool isFloat();


};

class StageDataPool{
    public:
    QQueue <StageData*> buffer;
    QList<StageData *> all;

    StageDataPool(){
        //Do nothing
    }
    ~StageDataPool(){
        //Kill all data
        for(StageData * data : all){
            delete data;
        }
    }

    StageData * get(){
        if(buffer.isEmpty() == false){
            qDebug() << "A";
            StageData * ret = buffer.dequeue();
            return ret;
        }
        else{
            StageData * ret = new StageData();
            all.append(ret);
            return ret;
        }
    }
    void kill(StageData * data){
        buffer.enqueue(data);
    }
};

#endif
