#include "Computer.h"
#include "ProgramManagerY.h"

#include <QDebug>

Computer::Computer(){
    qDebug() << "COM: Creating computer";
    regs = new Register();
    mems = new MemoryStructure(MAIN_MEMORY_DELAY, false);
    exec = new Baseline(regs, mems);
    currState = DEAD;
    qDebug() << "COM: Computer created"; 
} 
Computer::~Computer(){
    qDebug() << "COM: Removing Computer";
    delete regs;
    delete mems;
    delete exec;
    if(program != NULL){ 
        delete program;
    }
    qDebug() << "COM: Computer is removed!";
}


void Computer::init(QString fileName){
    qDebug() <<"COM: init";
    //Blocked 
    if(currState == BLOCKED){
        emit sendMessage(ThreadMessage(ThreadMessage::A_OKAY, {}));
        return;
    }
    if(currState != DEAD){
        emit sendMessage(ThreadMessage(ThreadMessage::A_ERROR, {"Stop current program first"}));
        return;
    }
    QVector<Value>* vec = new QVector<Value>();
    
    program = ProgramManagerX::loadProgram(fileName);

    if(program == NULL){
        emit sendMessage(ThreadMessage(ThreadMessage::A_ERROR, {"Program doesn't exist"}));
        return;
    }
    for(int i =0 ; i < program->size; i++){
        Value v = {program->instructions->at(i)};
        vec->append(v);
    }
    feedInstructions();


    exec->init();
    regs->init();
    mems->init();

    mems->_mainMemory->write(vec, 0);

    currState = PAUSED;
    emit sendMessage(ThreadMessage(ThreadMessage::A_OKAY, {}));
    emit sendMessage(ThreadMessage(ThreadMessage::A_STATE_CHANGE, {PAUSED}));
    emit sendMessage(ThreadMessage(ThreadMessage::A_UPDATE, {regs->getPC()}));
    return;
}
void Computer::feedInstructions(){
    QList<QVariant> instructions;
    for(int i =0 ;i <= program->instructionEndAddress/INSTRUCTION_SIZE; i++){
        if(program->instructionEndAddress <= program->dataEndAddress ){
            QVariant v = program->instructions->at(i);
            instructions.append(v);
        }
    }
    emit sendMessage(ThreadMessage(ThreadMessage::A_FEED, instructions));

}


void Computer::step(int nCycle, double _delay){
    qDebug() << "COM: step";
    //Blocked 
    if(currState == BLOCKED){
        emit sendMessage(ThreadMessage(ThreadMessage::A_OKAY, {}));
        return;
    } 
    if(currState == DEAD){
        emit sendMessage(ThreadMessage(ThreadMessage::A_ERROR, {"No program is running"}));
        return;
    }

    currState = RUNNING;
    emit sendMessage(ThreadMessage(ThreadMessage::A_STATE_CHANGE, {RUNNING}));
    emit sendMessage(ThreadMessage(ThreadMessage::A_OKAY, {}));


    while(currState == RUNNING){
        //sleep for sanity
        qDebug() << _delay;
        delay(_delay);

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
        if(_delay != 0){
            qDebug() << "A";
            emit sendMessage(ThreadMessage(ThreadMessage::A_UPDATE, {regs->getPC()}));
        }
    }

    //Distinguish from stop
    if(currState == PAUSED){
        emit sendMessage(ThreadMessage(ThreadMessage::A_UPDATE, {regs->getPC()}));
        emit sendMessage(ThreadMessage(ThreadMessage::A_STATE_CHANGE, {PAUSED}));
    }   
    return;
}

void Computer::stop(){
    qDebug() << "COM: stop";
    if(currState == BLOCKED){
        emit sendMessage(ThreadMessage(ThreadMessage::A_OKAY, {}));
        return;
    } 
    if(currState == DEAD){
        emit sendMessage(ThreadMessage(ThreadMessage::A_ERROR, {"No program is running"}));
        return;
    }
    currState = DEAD;
    exec->stop();
    program == NULL;
    emit sendMessage(ThreadMessage(ThreadMessage::A_OKAY, {}));
    emit sendMessage(ThreadMessage(ThreadMessage::A_STATE_CHANGE, {DEAD}));
    return;
}

void Computer::pause(){
    qDebug() << "COM: pause";
    if(currState == BLOCKED){
        emit sendMessage(ThreadMessage(ThreadMessage::A_OKAY, {}));
        return;
    } 
    if(currState == PAUSED || currState == DEAD){
        emit sendMessage(ThreadMessage(ThreadMessage::A_ERROR, {"Program is already paused"}));
        return;
    }
    currState = PAUSED;
    emit sendMessage(ThreadMessage(ThreadMessage::A_OKAY, {}));
}

//http://stackoverflow.com/questions/3752742/how-do-i-create-a-pause-wait-function-using-qt
void Computer::delay(double d)
{
    QTime dieTime= QTime::currentTime().addSecs(d);
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
    if(currState == BLOCKED){
        emit sendMessage(ThreadMessage(ThreadMessage::A_OKAY, {}));
        return;
    }  
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
void Computer::handleCacheView(int id){
    Cache * cache = (Cache *) mems->map[id];
    if(currState == BLOCKED){
        emit sendMessage(ThreadMessage(ThreadMessage::A_OKAY, {}));
        return;
    }

    if(mems->map.size() == 1){
        emit sendMessage(ThreadMessage(ThreadMessage::A_OKAY, {}));
        return;
    }
    QList<QVariant> list;
    list.append(id);
    int size =cache->contents->size();
    int _size=cache->contents->at(0)->size();
    int __size = cache->contents->at(0)->at(0)->size();
    int count =0;
    for(int ind = 0; ind < size && count <64; ind++) {
        for(int way = 0; way < _size && count < 64; way++) {
            for(int offset = 0; offset < __size && count < 64; offset++) {
                QList<QVariant> _list;
                _list.append(cache->valid->at(ind)->at(way));
                _list.append(cache->dirty->at(ind)->at(way));
                _list.append(cache->LRU->at(ind)->at(way));
                _list.append(cache->tags->at(ind)->at(way));
                _list.append(ind);
                _list.append(offset);
                _list.append(cache->contents->at(ind)->at(way)->at(offset).asInt);
                list.append(_list);
                count++;
            }
        }
    }
    emit sendMessage(ThreadMessage(ThreadMessage::A_VIEW_CACHE, list));
    return;
}
void Computer::handleRegisterView(QString line){
    qDebug() << "COM: make register view";
    if(currState == BLOCKED){
        emit sendMessage(ThreadMessage(ThreadMessage::A_OKAY, {}));
        return;
    } 
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
        uint content = regs->_flag.asUInt;
        ret.append(content);
        for(int row =0; row< 64; row++){
            uint content = regs->_flags[row].asUInt;
            ret.append(content);
        }
    }
    emit sendMessage(ThreadMessage(ThreadMessage::A_VIEW_REGISTER, ret));
    return;
}
void Computer::handleSaveState(QString fileName){
    if(currState != PAUSED){
        emit sendMessage(ThreadMessage(ThreadMessage::A_ERROR, {"Program must be paused"}));
        return;
    }
    currState = BLOCKED;

    if(ProgramManagerY::save(this, fileName) == false){
        emit sendMessage(ThreadMessage(ThreadMessage::A_ERROR, "save failed"));
        currState = PAUSED;
        return;
    }

    emit sendMessage(ThreadMessage(ThreadMessage::A_SAVE_STATE, {}));
    currState = PAUSED;
    return;
}

void Computer::handleRestoreState(QString fileName){
    if(currState != DEAD){
        qDebug() << currState;
        emit sendMessage(ThreadMessage(ThreadMessage::A_ERROR, {"Program must be stopped"}));
        return;
    }
    currState = BLOCKED;

    if(ProgramManagerY::restore(this,fileName) == false){
        emit sendMessage(ThreadMessage(ThreadMessage::A_ERROR, "restore failed"));
        currState = DEAD;
        return;
    }
    feedInstructions();

    //TODO maybe?

    currState = PAUSED;
    emit sendMessage(ThreadMessage(ThreadMessage::A_RESTORE_STATE, {}));
    emit sendMessage(ThreadMessage(ThreadMessage::A_STATE_CHANGE, {PAUSED}));
    emit sendMessage(ThreadMessage(ThreadMessage::A_UPDATE, {regs->getPC()}));
    qDebug() << regs->getPC();
    return;
}

void Computer::procMessage(ThreadMessage message){
    ThreadMessage::Type type = message.type;

    QVariant info = message.message;
    switch(type){
        case ThreadMessage::R_INIT:
            qDebug() << "COM: RECV FROM GUI: R_INIT";
            init(info.toString());
            break;
        case ThreadMessage::R_SET_PC:
            qDebug() << "COM: RECV FROM GUI: R_SET_PC";
            regs->write(info.toUInt(), Register::PC);
            emit sendMessage(ThreadMessage(ThreadMessage::A_SET_PC,{}));
            break;
        case ThreadMessage::R_STEP:
            qDebug() << "COM: RECV FROM GUI: R_STEP";
            step(info.toInt(), message.message2.toDouble());
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
        case ThreadMessage::R_VIEW_CACHE:
            qDebug() << "COM: RECV FROM GUI: R_VIEW_CACHE";
            handleCacheView(info.toInt());
            break;
        case ThreadMessage::R_SAVE_STATE:
            qDebug() << "COM: RECV FROM GUI: R_SAVE_STATE";
            handleSaveState(info.toString());
            break;
        case ThreadMessage::R_RESTORE_STATE:
            qDebug() << "COM: RECV FROM GUI: R_RESTORE_STATE";
            handleRestoreState(info.toString());
            break;
        case ThreadMessage::R_ADD_CACHE:
            qDebug() << "COM: RECV FROM GUI: R_ADD_CACHE";
            mems->addCache(info.toList()[0].toInt(), MemoryStructure::convert(info.toList()[1].toInt()), info.toList()[2].toInt(), info.toList()[3].toInt(),info.toList()[4].toInt(), info.toList()[5].toDouble());
            emit sendMessage(ThreadMessage(ThreadMessage::A_OKAY, {}));
            break;
        case ThreadMessage::R_REMOVE_CACHE:
            qDebug() << "COM: RECV FROM GUI: R_REMOVE_CACHE";
            mems->removeCache(info.toInt());
            emit sendMessage(ThreadMessage(ThreadMessage::A_OKAY, {}));
            break;
        default:
            qDebug() <<"COM: Invalid message";
            break;
    }

}

void Computer::step(int nCycle) {
    // TODO:  DESTROY THIS!!!
    step(nCycle, 1.0);
}
