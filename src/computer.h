#ifndef COMPUTER_H
#define COMPUTER_H

#include <QList>
#include  "memory/Cache.h"
#include "assembler/assembler.h"

class Computer{
    public:
        Cache* topCache = NULL;
        Assembly* assembly;
        
        bool update();
};   

#endif
