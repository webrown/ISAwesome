#ifndef BASELINE_H
#define BASELINE_H

#include "../memory/Register.h"
#include "../memory/MemoryStructure.h"
#include "../computer/Status.h"
#include "Banana.h"

class Baseline : public Banana{
    public:
        Register *registers;
        MemoryStructure  *memory;
        Baseline(Register *registers, MemoryStructure *memory);
        virtual ~Baseline();
        void init(void);
        Status run(void);
        void stop(void);
};
#endif
