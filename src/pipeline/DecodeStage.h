#ifndef DECODESTAGE_H
#define DECODESTAGE_H
#include "Stage.h" 
#include "PrefetchStage.h"
#include "ExecuteStage.h"
#include "../Utility.h"
#include "../memory/Register.h"
#include <QVector>
class DecodeStage : public Stage{
    public: 
        bool dependencyFlag; 
        Register * regs;
        void cycleDown(void);
        void cycleUp(void);
        bool isDependent(char regNum) const;
        bool isDependent(QVector<char> regNums) const;
        bool isDependent(StageData *) const;
};
#endif
