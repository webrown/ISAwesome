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
#include "../banana/Banana.h"
#include "../baseline/Baseline.h"
#include "Status.h"
#include "ThreadMessage.h"
#include <QThread>
#include "../pipeline/Pipeline.h"
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

        qint64 totalElapsed = 0;

        State currState;
        QMap<uint,BreakPoint::BreakPoint> breakMap;

        Register* regs = NULL;
        MemoryStructure* mems = NULL;

        Banana* exec = NULL;

        Program* program = NULL;

        Computer();
        ~Computer();



        //initialize computer module with selected program
        void init(QString fileName);

        //Run computer module for n cycles.
        //If n < 0, run indefinitely.
        void step(int nCycle, double delay);

        //Puase the program
        void pause();

        //Stop the program
        void stop();



        //Change behavior of computer
        void addBreakPoint(uint address, BreakPoint::BreakPoint bp);
        void handleChangeBanana(Banana::Type type);
        void handleSetPC();

        //Return requested view to Gui layer
        void handleTrackerView();
        void handleBananaView();
        void handlePerformanceView();
        void handleMemoryView(uint startAddress);
        void handleRegisterView(QString type);
        void handleCacheView(QList<QVariant> list);

        //Save/Restore State
        void handleSaveState(QString fileName);
        void handleRestoreState(QString fileName);

        //Wrapper funciton around sendMessage
        void sendMessage(ThreadMessage::Type type);
        void sendMessage(ThreadMessage::Type type, QVariant v1);
        void sendMessage(ThreadMessage::Type type, QVariant v1, QVariant v2);



        public slots:
            void procMessage(ThreadMessage message);
        signals:
        void _sendMessage(ThreadMessage message);

        private:
        void delay(double delay);


        public: 
        /*
         * TODO:  THIS IS EVIL.
         */
        void step(int nCycle);


};   
#endif
