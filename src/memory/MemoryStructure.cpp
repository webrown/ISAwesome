#include "MemoryStructure.h"

MemoryStructure::MemoryStructure(double mainMemoryDelay, bool isDummy) {
    MemoryInterface* dummyHead;
    if(isDummy){
        dummyHead = new DummyMem(Cache::BOTH, 32,0,0,MAIN_MEMORY_DELAY);
    }
    else {
        _mainMemory = new MainMemory(mainMemoryDelay);
        dummyHead = _mainMemory;
    }

    this->isDummy = isDummy;
    _lastAdded = dummyHead;
    _dataAccess = dummyHead;
    _instructionAccess = dummyHead;

    dummyHead->id = id++;
    map.insert(dummyHead->id, dummyHead);

}

MemoryStructure::~MemoryStructure() {
    for(int key : map.keys()){
        delete map[key];
    }
}

void MemoryStructure::init(){
    if(isDummy){
        qDebug() << "Can't init dummies";
        exit(-1);
    }
    for(int key : map.keys()){
        map[key]->init();
    }
}

bool MemoryStructure::addCache(int nextId, MemoryInterface::Type type, int indexBits, int logDataWordCount, int logAssociativity, double delay){
    // qDebug() << "---------add-------------";
    // qDebug() << "NEXT ID" << QString::number(nextId);
    // qDebug() << "NEXT TYPE" << QString::number(nextId);

    if(map.contains(nextId) == false){
        qDebug() << "Model not found, RIP";
        exit(-1);
    }
    MemoryInterface* next = map[nextId];
    //Under BOTH: DATA, INSTRUCITON and BOTH
    //Under DATA: DATA
    //Under INST: INST
    if(next->type == Cache::DATA_ONLY && type != Cache::DATA_ONLY){
        qDebug() << "GUI: !DATA under DATA";
        return false;
    }
    if(next->type == Cache::INSTRUCTION_ONLY && type != Cache::INSTRUCTION_ONLY){
        qDebug() << "GUI: !INST under INST";
        return false;
    }

    //Above BOTH: BOTH
    //Above DATA: BOTH and DATA
    //Above INST: BOTH and INSt
    MemoryInterface* prev = findPrev(next, Cache::BOTH);
    if(prev != NULL && prev->type == Cache::BOTH && type != Cache::BOTH){
        qDebug() << "GUI: !BOTH above BOTH";
        return false;
    }
    
    MemoryInterface* curr;
    if(isDummy){
        curr= new DummyMem(type, indexBits, logDataWordCount, logAssociativity, delay);
    }
    else{
        curr = new Cache(indexBits, logDataWordCount, logAssociativity,delay, NULL);
        curr->type = type;
    }
    curr->id = id;
    id++;

    MemoryInterface* prev_inst = findPrev(next, Cache::INSTRUCTION_ONLY);
    MemoryInterface* prev_data = findPrev(next, Cache::DATA_ONLY);

    if(type == Cache::INSTRUCTION_ONLY || type == Cache::BOTH){
        if(prev_inst == NULL){
            // qDebug() << "set inst head";
            _instructionAccess = curr;
        }
        else{
            // qDebug() << "not set inst head: " <<prev_inst->id;
            prev_inst->next = curr;
        }
    }
    if(type == Cache::DATA_ONLY || type == Cache::BOTH){
        if(prev_data == NULL){
            // qDebug() << "set data head";
            _dataAccess = curr;
        }
        else{
            // qDebug() << "not set data head: " <<prev_data->id;
            prev_data->next = curr;
        }
    }
    

    // qDebug() << "TYPE: " << type;
    // qDebug() << "ADD: " << id;
    _lastAdded = curr;

    map.insert(curr->id, curr);
    curr->next = next;
    
    return true;
}

bool MemoryStructure::removeCache(int id){
    if(map.contains(id) == false){
        qDebug() << "Invalid arguemtn exceptin";
        exit(-1);
    }
    MemoryInterface * curr = map[id]; 
    map.remove(id);
    MemoryInterface * next = curr->next;
    if(curr->type == Cache::BOTH){
        MemoryInterface * prev_inst = findPrev(curr, Cache::INSTRUCTION_ONLY);
        MemoryInterface * prev_data = findPrev(curr, Cache::DATA_ONLY);
        if(prev_inst == NULL){
            _instructionAccess = next;
        }
        else{
            prev_inst->next= next;
        }
        if(prev_data == NULL){
            _dataAccess = next;
        }
        else{
            prev_data->next = next;
        }
    }
    else if(curr->type == Cache::INSTRUCTION_ONLY){
        MemoryInterface * prev_inst = findPrev(curr, Cache::INSTRUCTION_ONLY);
        if(prev_inst == NULL){
            _instructionAccess = next;
        }
        else{
            prev_inst->next= next; }
    }
    else if(curr->type == Cache::DATA_ONLY){
        MemoryInterface * prev_data = findPrev(curr, Cache::DATA_ONLY);
        if(prev_data == NULL){
            _dataAccess = next;
        }
        else{
            prev_data->next = next;
        }
    }
    _lastAdded = curr;
    return true;
}

QStringList MemoryStructure::getNames(){
    QStringList ret;
    MemoryInterface* instM = _instructionAccess;
    MemoryInterface* dataM = _dataAccess;
    int level = 1;
    while(dataM->type != Cache::BOTH || instM->type != Cache::BOTH){
        if(instM->type != Cache::BOTH){
            ret << "Level " + QString::number(level) + " Cache(I)";
            instM = instM->next;
        }
        if(dataM->type != Cache::BOTH){
            ret << "Level " + QString::number(level) + " Cache(D)";
            dataM = dataM->next;
        }
        level++;
    }
    for(; instM != NULL; instM = instM->next){
        ret << "Level " + QString::number(level) + " Cache(I&D)";
        level++;
    }
    ret.removeLast();
    return ret;
}

MemoryInterface *MemoryStructure::findPrev(MemoryInterface* target, Cache::Type type){
    if(target == NULL){
        qDebug() << "Null pointer...";
        exit(-1);
    }
    if(type == Cache::DATA_ONLY){
        for(MemoryInterface* curr = _dataAccess; curr->next != NULL; curr = curr->next){
            if(curr->next == target){
                return curr;
            }
        }
        return NULL;
    }
    else if(type == Cache::INSTRUCTION_ONLY){
        for(MemoryInterface* curr = _instructionAccess; curr->next != NULL; curr = curr->next){
            if(curr->next == target){
                return curr;
            }
        }
        return NULL;
    }
    else{
        for(MemoryInterface* curr = _dataAccess; curr->next != NULL; curr = curr->next){
            if(curr->next == target){
                return curr;
            }
        }
        for(MemoryInterface* curr = _instructionAccess; curr->next != NULL; curr = curr->next){
            if(curr->next == target){
                return curr;
            }
        }
        return NULL;

    }


}

void MemoryStructure::setUpPlz(QComboBox * box, MemoryStructure * container){
    MemoryInterface* instM = container->_instructionAccess;
    MemoryInterface* dataM = container->_dataAccess;
    box->clear();
    int level = 1;
    while(dataM->type != Cache::BOTH || instM->type != Cache::BOTH){
        if(instM->type != Cache::BOTH){
            box->addItem("Level " + QString::number(level) + " Cache(I)", {instM->id});
            qDebug() << "INST " << instM->id << "->" <<instM->next->id;
            instM = instM->next;
        }
        if(dataM->type != Cache::BOTH){
            box->addItem("Level " + QString::number(level) + " Cache(D)", {dataM->id});
            qDebug() << "DATA " << dataM->id << "->" << dataM->next->id;
            dataM = dataM->next;

        }
        level++;
    }
    for(; instM != NULL; instM = instM->next){
        box->addItem("Level " + QString::number(level) + " Cache(I&D)", {instM->id});
        QString something = (instM->id ==0) ? "" : QString::number(instM->next->id);
            qDebug() << "BOTH " <<instM->id << "->" << something;

        level++;
    }
    box->removeItem(box->count()-1);
}

MemoryInterface *MemoryStructure::getDataAccess() {
    return _dataAccess;
}

MemoryInterface *MemoryStructure::getInstructionAccess() {
    return _instructionAccess;
}



//---------------------------_DEPRECATED---------------------------------
void MemoryStructure::pushCache(Cache *newCache) {
    newCache->next = _lastAdded;
    _lastAdded = newCache;
}

Cache *MemoryStructure::pushCache(int indexBits, int logDataWordCount, int logAssociativity, double delay) {
    Cache *result = new Cache(indexBits, logDataWordCount, logAssociativity, delay, NULL);
    pushCache(result);
    return result;
}

void MemoryStructure::goBack() {
    if(_lastAdded != _mainMemory) {
        _lastAdded = static_cast<Cache*>(_lastAdded)->next;
    }
}

void MemoryStructure::setToInstructionAccess() {
    _instructionAccess = _lastAdded;
}

void MemoryStructure::setToDataAccess() {
    _dataAccess = _lastAdded;
}
MemoryInterface *MemoryStructure::getLastAdded() {
    return _lastAdded;
}

