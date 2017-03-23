#ifndef BANANA_H
#define BANANA_H

#include "../memory/Register.h"
#include "../memory/MemoryStructure.h"
#include "../memory/MemoryStructure.h"
#include "../computer/Status.h"

class Banana {
    public:
        Banana(Register *registers, MemoryStructure *memory);
        ~Banana();
        virtual void init(void);
        virtual Status run(void);
        virtual void stop(void);
}
#endif
