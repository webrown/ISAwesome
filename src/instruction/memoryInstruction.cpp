#include "memoryInstruction.h"



class CPY:public Instruction{
    public:
        uint getOpcode(){
            return 4;
        }
        QString getName(){
            return "CPY";
        }
        uint parseOperands(QStringList ops, QString* m){
            if(!checkOpNum(2,ops,m)) return false;
        }
        QStringList unparseOperands(uint ops, QString* m){
        }
        void operate(uint ops){
        }
};


void MemoryInstructionLoader::load(QMap<QString, Instruction*> nameMap, QMap<uint, Instruction*> opcodeMap){
    //Add all instructions here!
    CPY* cpy= new CPY();
    nameMap["CPY"] = cpy;
    opcodeMap[4] = cpy;
}
