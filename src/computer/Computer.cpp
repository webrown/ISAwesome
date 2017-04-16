#include "Computer.h"
#include "ProgramManagerY.h"

#include <QDebug>

Computer::Computer(){
    qDebug() << "COM: Creating computer";
    currState = DEAD;

    //Set up memory related stuff
    regs = new Register();
    mems = new MemoryStructure(MAIN_MEMORY_DELAY, false);

    //Set up baseline
    exec = new Baseline(regs, mems);

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
    totalElapsed = 0;
    if(currState != DEAD){
        sendMessage(ThreadMessage::A_ERROR, {"Stop current program first"});
        return;
    }
    QVector<Value>* vec = new QVector<Value>();
    
    program = ProgramManagerX::loadProgram(fileName);

    if(program == NULL){
        sendMessage(ThreadMessage::A_ERROR, {"Program doesn't exist"});
        return;
    }
    for(int i =0 ; i < program->size; i++){
        Value v = {program->instructions->at(i)};
        vec->append(v);
    }
    handleTrackerView();


    exec->init();
    regs->init();
    mems->init();

    mems->_mainMemory->write(vec, 0);

    currState = PAUSED;
    sendMessage(ThreadMessage::A_OKAY);
    sendMessage(ThreadMessage::A_STATE_CHANGE, {PAUSED});
    sendMessage(ThreadMessage::A_UPDATE, {regs->getPC()});
    return;
}
void Computer::handleTrackerView(){
    //buffer for pipeline
    QList<QVariant> instructions;
    for(int i =0 ;i <= program->size; i++){
        if(i< program->instructionEndAddress){
            QVariant v = program->instructions->at(i);
            instructions.append(v);
        }
    }
    sendMessage(ThreadMessage::A_FEED, instructions);
}


void Computer::step(int nCycle, double _delay){
    qDebug() << "COM: step";
    if(currState == DEAD){
        sendMessage(ThreadMessage::A_ERROR, {"No program is running"});
        return;
    }

    currState = RUNNING;
    sendMessage(ThreadMessage::A_STATE_CHANGE, {RUNNING});
    sendMessage(ThreadMessage::A_OKAY);
    // timer.restart();
    QTime timer;
    timer.start();

    while(currState == RUNNING){
        //sleep for sanity
        delay(_delay);

        
        uint pc; 
        Pipeline* ppp = dynamic_cast<Pipeline*>(exec) ;
        if( ppp== NULL){
            pc= regs->getPC(); 
        }
        else{
            pc= ppp->getPCinWriteStage();
        }

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
        if(_delay > 0.05){
            sendMessage(ThreadMessage::A_UPDATE, {regs->getPC()});
        }
    }
    totalElapsed += timer.elapsed();

    //Distinguish from stop
    if(currState == PAUSED){
        sendMessage(ThreadMessage::A_UPDATE, {regs->getPC()});
        sendMessage(ThreadMessage::A_STATE_CHANGE, {PAUSED});
    }   
    return;
}

void Computer::stop(){
    qDebug() << "COM: stop";
    if(currState == DEAD){
        sendMessage(ThreadMessage::A_ERROR, {"No program is running"});
        return;
    }
    breakMap.clear();
    currState = DEAD;
    exec->stop();
    program == NULL;
    sendMessage(ThreadMessage::A_OKAY, {});
    sendMessage(ThreadMessage::A_STATE_CHANGE, {DEAD});
    return;
}

void Computer::pause(){
    qDebug() << "COM: pause";
    if(currState == PAUSED || currState == DEAD){
        sendMessage(ThreadMessage::A_ERROR, {"Program is already paused"});
        return;
    }
    currState = PAUSED;
    sendMessage(ThreadMessage::A_OKAY);
}

//http://stackoverflow.com/questions/3752742/how-do-i-create-a-pause-wait-function-using-qt
void Computer::delay(double d)
{
    QTime dieTime= QTime::currentTime().addMSecs(d * 1000);
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
    sendMessage(ThreadMessage::A_OKAY, {});
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
        for(int row = 0; row < 256; row++){
            ret.append(0u);
        }
    }
    else{
        for(uint i = 0; i < 256; i++){
            uint content = mems->_mainMemory->_contents[chunkBit][x + i * INSTRUCTION_SIZE].asUInt;
            ret.append(content);
        }
    }
    sendMessage(ThreadMessage::A_VIEW_MEMORY, ret);
    return;
}
void Computer::handleCacheView(QList<QVariant> arg){
    int id = arg.takeFirst().toInt();
    Cache * cache = (Cache *) mems->map[id];

    if(mems->map.size() == 1){
        sendMessage(ThreadMessage::A_OKAY);
        return;
    }

    bool tagB = arg[0].toString() == "" ? false : true;
    bool indexB = arg[1].toString() == "" ? false : true;
    bool offsetB = arg[2].toString() == "" ? false : true;
    bool okay;
    uint tagS, indexS, offsetS;
    uint tagM = 1, indexM = 1, offsetM = 1;
    if(tagB == true){
        tagS = arg[0].toString().toUInt(&okay,2);
        if(okay == false){
            sendMessage(ThreadMessage::A_ERROR, {"Invalid argument for tag"});
            return;
        }
        for(int i =0 ; i < arg[0].toString().length(); i ++){
            tagM <<= 1;
        }
        tagM -=1;
    }
    if(indexB == true){
        indexS = arg[1].toString().toUInt(&okay,2);
        if(okay == false){
            sendMessage(ThreadMessage::A_ERROR, {"Invalid argument for index"});
            return;
        }
        for(int i =0 ; i < arg[1].toString().length(); i ++){
            indexM <<= 1;
        }
        indexM -=1;
    }
    if(offsetB == true){
        offsetS = arg[2].toString().toUInt(&okay,2);
        if(okay == false){
            sendMessage(ThreadMessage::A_ERROR, {"Invalid argument for offset"});
            return;
        }
        for(int i =0 ; i < arg[2].toString().length(); i ++){
            offsetM <<= 1;
        }
        offsetM -=1;
    }
    // qDebug() << QString::number(tagS, 2);
    
    // qDebug() << QString::number(tagM, 2);

    QList<QVariant> list;
    list.append(id);
    int size =cache->contents->size();
    int _size=cache->contents->at(0)->size();
    int __size = cache->contents->at(0)->at(0)->size();
    int count =0;
    int min = arg[3].toInt();
    int max = arg[3].toInt() + 64;
    for(int ind = 0; ind < size && count <max; ind++) {
        uint indV = ind & indexM;
        // qDebug() << indexB <<indV << indexS;
        if(indexB == true && indV != indexS){
            continue;
        }
        for(int way = 0; way < _size && count < max; way++) {
            for(int offset = 0; offset < __size && count < max; offset++) {

                uint offsetV = offset & offsetM;
                // qDebug() << offsetB <<offsetV << offsetS;

                if(offsetB == true && offsetV != offsetS){

                    continue;
                }
                uint tagBit = cache->tags->at(ind)->at(way);
                uint tagV = tagBit & tagM;
                // qDebug() << tagB <<tagV << tagS;

                if(tagB == true && tagV != tagS){
                    continue;
                }
                //TODO check this
                if(count++ < min){
                    continue;
                }
                QList<QVariant> _list;
                _list.append(cache->valid->at(ind)->at(way));
                _list.append(cache->dirty->at(ind)->at(way));
                _list.append(cache->LRU->at(ind)->at(way));
                _list.append(cache->tags->at(ind)->at(way));
                _list.append(ind);
                _list.append(offset);
                _list.append(cache->contents->at(ind)->at(way)->at(offset).asInt);
                list.append(_list);
            }
        }
    }
    list <<count;
    sendMessage(ThreadMessage::A_VIEW_CACHE, list);
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
        uint content = regs->_flag.asUInt;
        ret.append(content);
        for(int row =0; row< 64; row++){
            uint content = regs->_flags[row].asUInt;
            ret.append(content);
        }
    }
    sendMessage(ThreadMessage::A_VIEW_REGISTER, ret);
    return;
}
void Computer::handleSaveState(QString fileName){
    if(currState != PAUSED){
        sendMessage(ThreadMessage::A_ERROR, {"Program must be paused"});
        return;
    }
    currState = BLOCKED;

    if(ProgramManagerY::save(this, fileName) == false){
        sendMessage(ThreadMessage::A_ERROR, "save failed");
        currState = PAUSED;
        return;
    }

    sendMessage(ThreadMessage::A_SAVE_STATE);
    currState = PAUSED;
    return;
}

void Computer::handleRestoreState(QString fileName){
    if(currState != DEAD){
        qDebug() << currState;
        sendMessage(ThreadMessage::A_ERROR, {"Program must be stopped"});
        return;
    }
    currState = BLOCKED;

    if(ProgramManagerY::restore(this,fileName) == false){
        sendMessage(ThreadMessage::A_ERROR, "restore failed");
        currState = DEAD;
        return;
    }
    handleTrackerView();

    //TODO maybe?
    currState = PAUSED;
    sendMessage(ThreadMessage::A_RESTORE_STATE, {});
    sendMessage(ThreadMessage::A_STATE_CHANGE, {PAUSED});
    sendMessage(ThreadMessage::A_UPDATE, {regs->getPC()});
    // qDebug() << regs->getPC();
    return;
}
void Computer::handleChangeBanana(Banana::Type type){
    qDebug() << "COM: handle banana change";
    if(currState != DEAD){
        sendMessage(ThreadMessage::A_ERROR, {"Program must be stopped first"});
        return;
    }
    if(type == Banana::PIPELINE){
        if(dynamic_cast<Pipeline*>(exec) == NULL){
            delete exec;
            exec = new Pipeline(regs, mems);
            sendMessage(ThreadMessage::A_CHANGE_BANANA, {Banana::PIPELINE});
            return;
        }
        else{
            sendMessage(ThreadMessage::A_ERROR, {"Program is already using Pipeline"});
            return;
        }
    }
    else if(type == Banana::BASELINE){
        if(dynamic_cast<Baseline*>(exec) == NULL){
            delete exec;
            exec = new Baseline(regs, mems);
            sendMessage(ThreadMessage::A_CHANGE_BANANA, {Banana::BASELINE});
            return;
        }
        else{
            sendMessage(ThreadMessage::A_ERROR, {"Program is already using Baseline"});
            return;
        }
    }
    
}
void Computer::handleBananaView(){
    qDebug() << "COM: handle Banana View";
    //Baseline
       QList<QVariant> data;
    if(dynamic_cast<Pipeline*>(exec) == NULL){
       Baseline* baseline = dynamic_cast<Baseline*>(exec); 
       for(int i =0; i < 5; i++){
           data.append(false);
           data.append(false);
           data.append(false);
           // qDebug() << baseline->_instructionFetchWait;
           if(baseline->_instructionFetchWait >0){
                data.append(baseline->_instructionFetchWait);
                data.append("Fetching...");
           }
           else{
               data.append(baseline->_waitLeft);
               data.append(QString::number(baseline->nextInstruction));
           }
       }
    }
    //Pipeline
    else{
        Pipeline* pipeline = dynamic_cast<Pipeline*>(exec);
        for(Stage * stage = &(pipeline->prefetchStage); stage != NULL; stage = stage->next){

            StageData * d = stage->currData;
            if(d == NULL){
                data.append(false);
                data.append(false);
                data.append(false);
                data.append(0);
                data.append("N/A");
            }
            else{
            data.append(stage->structureFlag);
            data.append(stage->dependencyFlag);
            data.append(d->isSquashed());
            data.append(stage->delay >= 0 ? stage->delay : 0);
            data.append(QString::number(d->instruction));
            }
        }
        qDebug() << data.size();
    }
    sendMessage(ThreadMessage::A_VIEW_BANANA, data);

    
}
void Computer::handlePerformanceView(){
    qDebug() << "COM: handle performance view";

    QMap<QString, QVariant> map;
    map["/General/Cycle/Total"] = exec-> cyclesDone;
    map["/General/Cycle/CPI"] = (double) exec->cyclesDone / exec->instructionsDone;
    map["/General/Cycle/IPC"] = (double) exec->instructionsDone / exec->cyclesDone;
    map["/Instruction/Total"] = exec->instructionsDone;
    map["/General/Time/Total"] = totalElapsed;
    map["/General/Time/IPT"] = (double) exec->cyclesDone / totalElapsed;
    map["/General/Time/CPT"] =  (double) exec->instructionsDone / totalElapsed;

    for(QPair<QString, int> str : this->mems->getIds()){
        QString entry = "/Memory/" + str.first;
        Cache * cache = (Cache* )this->mems->map[str.second];
        qint64 total = cache->hit + cache->compulsuryMiss + cache->conflictMiss;
        map[entry + "/Stat/HitRate"] = (double)cache->hit / total;
        map[entry + "/Stat/HitCount"] = cache->hit;
        map[entry + "/Stat/CompulsuryMiss"] = cache->compulsuryMiss;
        map[entry + "/Stat/ConflictMiss"] = cache->conflictMiss;
    }
    map["/Memory/Ram/Page"] = mems->_mainMemory->memoryInUse;

    if(dynamic_cast<Baseline*>(exec) == NULL){
        map["/Alu/Type"] = "Pipeline";
    }
    else{
        map["/Alu/Type"] = "Baseline";

    }




    sendMessage(ThreadMessage::A_VIEW_PERFORMANCE, map);
    return; 
}
void Computer::procMessage(ThreadMessage message){
    ThreadMessage::Type type = message.type;
    if(currState == BLOCKED){
        sendMessage(ThreadMessage::A_OKAY);
        return;
    }

    QVariant info = message.message;
    switch(type){
        case ThreadMessage::R_INIT:
            qDebug() << "COM: RECV FROM GUI: R_INIT";
            init(info.toString());
            break;
        case ThreadMessage::R_SET_PC:
            qDebug() << "COM: RECV FROM GUI: R_SET_PC";
            regs->write(info.toUInt(), Register::PC);
            sendMessage(ThreadMessage::A_SET_PC,{});
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
        case ThreadMessage::R_VIEW_BANANA:
            qDebug() << "COM: RECV FROM GUI: R_VIEW_BANANA";
            handleBananaView();
            break;
        case ThreadMessage::R_VIEW_MEMORY:
            qDebug() << "COM: RECV FROM GUI: R_VIEW_MEMORY";

            handleMemoryView(info.toUInt());
            break;
        case ThreadMessage::R_VIEW_CACHE:
            qDebug() << "COM: RECV FROM GUI: R_VIEW_CACHE";
            handleCacheView(info.toList());
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
            sendMessage(ThreadMessage::A_OKAY);
            break;
        case ThreadMessage::R_REMOVE_CACHE:
            qDebug() << "COM: RECV FROM GUI: R_REMOVE_CACHE";
            mems->removeCache(info.toInt());
            sendMessage(ThreadMessage::A_OKAY);
            break;
        case ThreadMessage::R_CLEAR_CACHE:
            qDebug() << "COM: RECV FROM GUI: R_CLEAR_CACHE";
            mems->clear();
            sendMessage(ThreadMessage::A_OKAY, {});
            break;
        case ThreadMessage::R_VIEW_PERFORMANCE:
            qDebug() << "COM: RECV FROM GUI: R_VIEW_PERFORMANCE";
            handlePerformanceView();
            break;
        case ThreadMessage::R_CHANGE_BANANA:
            qDebug() << "COM: RECV FROM GUI: R_BANANA_CHANGE";
            handleChangeBanana(static_cast<Banana::Type>(info.toInt()));
            break;
        default:
            qDebug() <<"COM: Invalid message";
            break;
    }

}

void Computer::sendMessage(ThreadMessage::Type type){
    emit _sendMessage(ThreadMessage(type, {}));
}
void Computer::sendMessage(ThreadMessage::Type type, QVariant v1){
    emit _sendMessage(ThreadMessage(type, v1));
}
void Computer::sendMessage(ThreadMessage::Type type, QVariant v1, QVariant v2){
    emit _sendMessage(ThreadMessage(type, v1, v2));
}


//@@@@@@@@@@@@@@@@@DEPRECATED#@@@@@@@@@@@@@@@@@@@@
void Computer::step(int nCycle) {
    // TODO:  DESTROY THIS!!!
    step(nCycle, 1.0);
}
