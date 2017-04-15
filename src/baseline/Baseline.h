#ifndef BASELINE_H
#define BASELINE_H

#include "../memory/Register.h"
#include "../memory/MemoryStructure.h"
#include "../computer/Status.h"
#include "../banana/Banana.h"

class Baseline : public Banana{
    public:
        Register *registers;
        MemoryStructure  *memory;
        int _waitLeft;

        Baseline(Register *regs, MemoryStructure *mem);
        virtual ~Baseline();
        void init(void);
        Status run(void);
        void stop(void);
};
#endif
