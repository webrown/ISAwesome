#include "Computer.h"
#include <QDebug>

Computer::Computer(){
    qDebug() << "COM: Creating computer";
    regs = new Register();
    mems = new MemoryStructure(MAIN_MEMORY_DELAY);
    exec = new Baseline(regs, mems);
    currState = DEAD;
    qDebug() << "COM: Computer created"; } Computer::~Computer(){
        qDebug() << "COM: Removing Computer";
        delete regs;
        delete mems;
        delete exec;
        qDebug() << "COM: Computer is removed!";
    }

void Computer::init(QList<QVariant> instructions){
    qDebug() <<"COM: init";
    if(currState != DEAD){
        emit sendMessage(ThreadMessage(ThreadMessage::A_ERROR, {"Stop current program first"}));
        return;
    }
    exec->init();
    regs->init();
    mems->init();

    QVector<Value>* vec = new QVector<Value>();
    for(int i =0 ; i < instructions.size(); i++){
        uint instruction = instructions[i].toUInt(); 
        Value v = {instruction};
        vec->append(v);
    }
    mems->_mainMemory->write(vec, 0);

    currState = PAUSED;
    emit sendMessage(ThreadMessage(ThreadMessage::A_OKAY, {}));
    emit sendMessage(ThreadMessage(ThreadMessage::A_STATE_CHANGE, {PAUSED}));
    emit sendMessage(ThreadMessage(ThreadMessage::A_UPDATE, {regs->getPC()}));
    return;
}


void Computer::step(int nCycle){
    qDebug() << "COM: step";
    if(currState == DEAD){
        emit sendMessage(ThreadMessage(ThreadMessage::A_ERROR, {"No program is running"}));
        return;
    }
    currState = RUNNING;
    emit sendMessage(ThreadMessage(ThreadMessage::A_STATE_CHANGE, {RUNNING}));
    emit sendMessage(ThreadMessage(ThreadMessage::A_OKAY, {}));


    while(currState == RUNNING){
        //sleep for sanity
        delay();

        uint pc = regs->getPC(); 

        bool skip = false;
        //Stop mechanism
        if(breakMap.contains(pc) == true){
            BreakPoint::BreakPoint bp = breakMap[pc];
            switch(bp){
                case BreakPoint::BREAK:
                    breakMap.remove(pc);
                case BreakPoint::BREAK_ALL:
                    currState = PAUSED;
                    break;
                case BreakPoint::SKIP:
                    breakMap.remove(pc);
                case BreakPoint::SKIP_ALL:
                    regs->write({regs->getPC()+INSTRUCTION_SIZE}, Register::PC);
                    skip = true;
                    break;
                case BreakPoint::NONE:
                default:
                    //Do nothing
                    break;
            }
        }

        if(skip == false){
            Status status = exec->run();
            if(status != OKAY){
                qDebug() << "Something is wrong; I feel like I have to do something, but I don't wnat to do anything.";
                return;
            }
        }



        nCycle = nCycle < 0 ? -1 : nCycle -1;
        if(nCycle == 0){
            currState = PAUSED;
        }
        emit sendMessage(ThreadMessage(ThreadMessage::A_UPDATE, {regs->getPC()}));
    }

    //Distinguish from stop
    if(currState == PAUSED){
        emit sendMessage(ThreadMessage(ThreadMessage::A_STATE_CHANGE, {PAUSED}));
    }   
    return;
}

void Computer::stop(){
    qDebug() << "COM: stop";
    if(currState == DEAD){
        emit sendMessage(ThreadMessage(ThreadMessage::A_ERROR, {"No program is running"}));
        return;
    }
    currState = DEAD;
    exec->stop();
    emit sendMessage(ThreadMessage(ThreadMessage::A_OKAY, {}));
    emit sendMessage(ThreadMessage(ThreadMessage::A_STATE_CHANGE, {DEAD}));
    return;
}

void Computer::pause(){
    qDebug() << "COM: pause";
    if(currState == PAUSED || currState == DEAD){
        emit sendMessage(ThreadMessage(ThreadMessage::A_ERROR, {"Program is already paused"}));
        return;
    }
    currState = PAUSED;
    emit sendMessage(ThreadMessage(ThreadMessage::A_OKAY, {}));
}

//http://stackoverflow.com/questions/3752742/how-do-i-create-a-pause-wait-function-using-qt
void Computer::delay()
{
    QTime dieTime= QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void Computer::addBreakPoint(uint address, BreakPoint::BreakPoint bp){
    qDebug() << "COM: add break point";
    if(bp == BreakPoint::NONE){
        breakMap.remove(address);
    }
    else{
        breakMap[address] = bp;
    }
    emit sendMessage(ThreadMessage(ThreadMessage::A_OKAY, {}));

}



void Computer::handleMemoryView(uint address){
    qDebug() <<"COM: make memory view";
    QList<QVariant> ret;
    //Put requested address in first index to display them
    ret.append(address);

    uint mask = (MainMemory::MEMORY_CHUNKS-1) << 8;
    uint chunkBit = ((mask & address) >> 8);
    uint x = (((1<<8)-1) & address) << 8;
    //check empty
    if(mems->_mainMemory->_contents[chunkBit].size() ==0){
        for(int row = 0; row < 64; row++){
            ret.append(0u);
        }
    }
    else{
        for(uint i = 0; i < 64; i++){
            uint content = mems->_mainMemory->_contents[chunkBit][x + i * INSTRUCTION_SIZE].asUInt;
            ret.append(content);
        }
    }
    emit sendMessage(ThreadMessage(ThreadMessage::A_VIEW_MEMORY, ret));
    return;
}

void Computer::handleRegisterView(QString line){
    qDebug() << "COM: make register view";
    QList<QVariant> ret;
    ret.append(line);
    if(line == "General Registers"){
        int row =0;
        for(;row < 24; row++){
            uint content = regs->_scas[row].asUInt;
            ret.append(content);
        }

        for(;row<64;row++){
            ret.append(0u);
        }
    }
    else if(line.startsWith("Integer Vector #")){
        int num = line.remove("Integer Vector #").toInt();
        for(int row =0; row< 64; row++){
            uint content = regs->_vecs[num][row].asUInt;
            ret.append(content);
        }
    }
    else if(line.startsWith("Float Vector #")){
        int num = line.remove("Float Vector #").toInt();
        for(int row =0; row< 64; row++){
            uint content = regs->_vecs[num + 4][row].asUInt;
            ret.append(content);
        }
    } 
    else if(line == "Flag Registers"){
        for(int row =0; row< 64; row++){
            uint content = regs->_flags[row].asUInt;
            ret.append(content);
        }
    }
    emit sendMessage(ThreadMessage(ThreadMessage::A_VIEW_REGISTER, ret));
    return;
}
void Computer::procMessage(ThreadMessage message){
    ThreadMessage::Type type = message.type;

    QVariant info = message.message;
    switch(type){
        case ThreadMessage::R_INIT:
            qDebug() << "COM: RECV FROM GUI: R_INIT";
            init(info.toList());
            break;
        case ThreadMessage::R_SET_PC:
            qDebug() << "COM: RECV FROM GUI: R_SET_PC";
            regs->write(info.toUInt(), Register::PC);
            emit sendMessage(ThreadMessage(ThreadMessage::A_SET_PC,{}));
            break;
        case ThreadMessage::R_STEP:
            qDebug() << "COM: RECV FROM GUI: R_STEP";
            step(info.toInt());
            break;
        case ThreadMessage::R_STOP:
            qDebug() << "COM: RECV FROM GUI: R_STOP";

            stop();
            break;
        case ThreadMessage::R_PAUSE:
            qDebug() << "COM: RECV FROM GUI: R_PAUSE";

            pause();
            break;
        case ThreadMessage::R_ADDBREAK:
            qDebug() << "COM: RECV FROM GUI: R_ADDBREAK";

            addBreakPoint(info.toList()[0].toUInt(), static_cast<BreakPoint::BreakPoint> (info.toList()[1].toUInt()));
            break;
        case ThreadMessage::R_VIEW_REGISTER:
            qDebug() << "COM: RECV FROM GUI: R_VIEW_REGISTER";

            handleRegisterView(info.toString());
            break;
        case ThreadMessage::R_VIEW_MEMORY:
            qDebug() << "COM: RECV FROM GUI: R_VIEW_MEMORY";

            handleMemoryView(info.toUInt());
            break;
        default:
            qDebug() <<"COM: Invalid message";
            break;
    }

}
