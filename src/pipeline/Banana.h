#ifndef BANANA_H
#define BANANA_H

#include "../memory/Register.h"
#include "../memory/MemoryStructure.h"
#include "../memory/MemoryStructure.h"
#include "../computer/Status.h"

class Banana {
    public:
        virtual void init(void) = 0;
        virtual Status run(void) = 0;
        virtual void stop(void) = 0;
};
#endif
