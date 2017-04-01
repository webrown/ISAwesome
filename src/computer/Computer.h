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
#include <QFile>
#include <QTimer>
#include "../assembler/Assembler.h" 
#include "../assembler/ProgramManagerX.h"

class Computer: public QObject{
    Q_OBJECT
    public:
        enum State{
            DEAD = 0,  RUNNING =1 , PAUSED = 2, BLOCKED =3
        };
        /*
         * If this variable is true, then computer will stop with break (I am not hundred percent sure about how to implement "break functionality"
         * If this variable is false, all break will be ignored
         */

        qint64 totalElapsed = 0;

        State currState;
        QMap<uint,BreakPoint::BreakPoint> breakMap;

        Register* regs = NULL;
        MemoryStructure* mems = NULL;
        Banana* exec = NULL;
        Program* program = NULL;

        Computer();
        ~Computer();

        /* 
         * Initiate computer, after step, pause, stop will be called only after init is called
         *
         */
        void init(QString fileName);

        
        /*
         * Run this computer for nCycle 
         * If nCycle = -1, run indefintely
         */
        void step(int nCycle, double delay);


        /*
         * TODO:  THIS IS EVIL.
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

        void feedInstructions();
        void delay(double delay);
        void addBreakPoint(uint address, BreakPoint::BreakPoint bp);
        void handlePerformance();
        void handleMemoryView(uint startAddress);
        void handleRegisterView(QString type);
        void handleSaveState(QString fileName);
        void handleRestoreState(QString fileName);
        void handleCacheView(QList<QVariant> list);

        public slots:
            void procMessage(ThreadMessage message);
        signals:
            void sendMessage(ThreadMessage message);
};   
#endif
