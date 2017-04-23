#ifndef STAGE_H
#define STAGE_H
#include <stdio.h>
#include <QDebug>
#include "StageData.h"

/* DO NOT MAKE CONSTRUCTOR FOR ANY SUBCLASSES
 */
class Stage{
    public:
        Stage *next = NULL;
        Stage *prev = NULL;

        StageData* currData = NULL;
        bool structureFlag = false;
        bool dependencyFlag = false; 
        int delay;
        bool computing;
        
        void init(void){
            currData = NULL;
            structureFlag = false;
            delay = 0;
        }
        virtual void cycleUp(void) = 0; 
        virtual void cycleDown(void) = 0; 

};
#endif
