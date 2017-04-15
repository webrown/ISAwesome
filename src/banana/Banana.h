#ifndef BANANA_H
#define BANANA_H

#include "../memory/Register.h"
#include "../memory/MemoryStructure.h"
#include "../memory/MemoryStructure.h"
#include "../computer/Status.h"

class Banana {
    public:
        enum Type{
            BASELINE = 0, PIPELINE =1
        };
        virtual void init(void)=0;
        virtual Status run(void)=0;
        virtual void stop(void)=0;
        qint64 instructionsDone =0;
        qint64 cyclesDone = 0;
};
#endif
