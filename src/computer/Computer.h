#ifndef COMPUTER_H
#define COMPUTER_H

#include <queue>
#include <QList>
#include <QTime>
#include <QCoreApplication>
#include <QQueue>
#include <QMap>
#include "../memory/Register.h"
#include "../memory/MemoryStructure.h"
#include "BreakPoint.h"
#include "../pipeline/Banana.h"
#include "../pipeline/Baseline.h"
#include "Status.h"
#include "ThreadMessage.h"
#include <QThread>
class Computer: public QObject{
    Q_OBJECT
    public:
        enum State{
            DEAD = 0,  RUNNING =1
        };
        /*
         * If this variable is true, then computer will stop with break (I am not hundred percent sure about how to implement "break functionality"
         * If this variable is false, all break will be ignored
         */

        State currState;
        bool breakEnabled = true;
        QMap<uint,BreakPoint::BreakPoint> breakMap;

        Register* regs = NULL;
        MemoryStructure* mems = NULL;
        Banana* exec = NULL;

        Computer();
        ~Computer();

        /* 
         * Initiate computer, after step, pause, stop will be called only after init is called
         *
         */
        void init(QList<QVariant> instructions);

        
        /*
         * Run this computer for nCycle 
         * If nCycle = -1, run indefintely
         */
        void step(int nCycle);
        
        /*
         * Pause the cycle of computer
         * If pause is called, during step, then remember the current step that the computer was it
         */
        void pause();
        
        /*
         * Kill the current program
         * This is different from removing the computer, it simply flushes out memory and pipeline
         */
        void stop();

        void delay();
        void addBreakPoint(uint address, BreakPoint::BreakPoint bp);
        void removeBreakPoint(uint address);

        void handleMemoryView(uint startAddress);
        void handleRegisterView(QString type);

        public slots:
            void procMessage(ThreadMessage message);
        signals:
            void sendMessage(ThreadMessage message);
};   
#endif
