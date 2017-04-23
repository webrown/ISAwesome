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
        Register * regs;
        void cycleDown(void);
        bool cycleUp(void);
        bool _dependencyFlag = false;
        bool isDependent(char regNum) const;
        bool isDependent(QVector<char> regNums) const;
        bool isDependent(StageData *) const;
};
#endif
