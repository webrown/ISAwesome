#ifndef BASELINE_H
#define BASELINE_H
#include "../memory/Register.h"
#include "../memory/MemoryStructure.h"
class Baseline {
    public:
        Register *_registers;
        MemoryStructure  *_memory;
        Baseline(Register *registers, MemoryStructure *memory);
        ~Baseline();
        void init(void);
        void run(void);
        void stop(void);
}
#endif
