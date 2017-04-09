#ifndef STAGEDATA_H
#define STAGEDATA_H
#include "../banana/PipelineGlobals.h"
#include "../memory/Value.h"
#include <QVector>
#include <QQueue>
#include <QDebug>
#include <QMap>

//based on https://en.wikipedia.org/wiki/Classic_RISC_pipeline
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
        char condFlag;

        //Opcode
        Opcode::Opcode opcode;

        //Destination
        char destReg;

        //This will be 32 bit long bit array.
        unsigned int regInUse;


        Value src;
        Value dest;
        Value aux;

        QVector<Value> srcVec;
        QVector<Value> destVec;

        bool isSquashed(){
            return (info & 1 == 1);
        }
        bool isVector(){
            return (info & 4 == 4);
        }
        bool isFloat(){
            return (info * 8 == 8);
        }
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
