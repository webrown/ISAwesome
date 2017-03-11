#ifndef INSTRUCTIONRESOLVER_H
#define INSTRUCTIONRESOLVER_H
#include <QMap>
#include "../utility.h"

#define OP_IMMI 1
#define OP_REG 2
#define OP_VEC 3
#define OP_IMMI22 4
#define OP_NONE 0

enum ArgumentType{
    INVALID = 0,
    I = 1,
    I22 = 2,
    R = 4,
    V = 8,
    IR = 16,
    IV = 32,
    RR = 64,
    RV = 128,
    VR = 256,
    VV = 512,
    RVI = 1024,
    RVR = 2048,
    VIR = 4096,
    VRR = 8192
};

class InstructionDefinition{
    public:
        QString name;
        uint opcode;
        uint (*parse)(QStringList);
        QStringList (*unparse)(uint);

        InstructionDefinition(QString name, uint opcode,uint (*parseFunc)(QStringList), QStringList (*unparseFunc)(uint) ){
            this->name = name;
            this->opcode = opcode;
            this->parse = parseFunc;
            this->unparse = unparseFunc;
        }
};

uint parseBranch(QStringList token){
}

class InstructionResolver{
    public:
        QMap<QString, InstructionDefinition*> nameTable;
        QMap<uint, InstructionDefinition*> opcodeTable;
        //    const QTable<uint, Instruction> instructionTable;
        void set(QString name, uint opcode, uint (*parseFunc)(QStringList), QStringList (*unparseFunc)(uint)){
            InstructionDefinition* inst = new InstructionDefinition(name, opcode, parseFunc, unparseFunc);
            nameTable[name] = inst;
            opcodeTable[opcode] = inst;
        }

        InstructionResolver(){

            // Branch
            set("B", 0x0, parseBranch, NULL);

            // Branch with register
            set("BL", 0x1, R);

            // Compare
            set("CMP",0x3, RR|IR|RV|IV|VV);

            // CPY
            set("CPY", 0x4, IR|RR|VV|RV);

            // LOD
            set("LOD", 0x5, RR|RV);

            // STO
            set("STO", 0x6, RR|VR);

            // RVE
            set("RVE",0x8,VIR|VRR);

            // Write vector
            set("WVE",0x9,RVR |RVI);

            //Move down
            set("MVD",0xA,VV|RV|IV);

            //Move Up
            set("MVU",0xB,VV|RV|IV);

            //Arrange
            set("ARR",0xC,VV);

            //Sequence
            set("SEQ",0xD,V);
            //Mulptiply elements
            set("MOE",0xE,VR);

            //Sum elements
            set("SOE",0XF,VR);

            //Add
            set("ADD", toB("010000"),RR|IR|RV|IV|VV);

            //ADDS
            set("ADDS",toB("010001"),RR|IR|RV|IV|VV);

            //ADC
            set("ADC", toB("010010"),RR|VV);

            //ADCS
            set("ADCS",toB("010011"),RR|VV);

            //Subtract
            set("SUB",toB("010100"),RR|IR|RV|IV|VV);

            //Subtract set
            set("SUBS",toB("010101"),RR|IR|RV|IV|VV);

            //Subtract carry
            set("SBC",toB("010110"),RR|VV);

            //Subtract carry set
            set("SBCS",toB("010111"),RR|VV);

            //Multiply
            set("MUL",toB("011000"),RR|IR|RV|IV|VV);

            //Multiply set
            set("MULS", toB("011001"),RR|IR|RV|IV|VV);

            //Long multiply
            set("LMUL", toB("011010"),RR|VV);

            //Long multiply set
            set("LMULS",toB("011011"),RR|VV);

            //divide
            set("DIV", toB("011100"),RR|IR|RV|IV|VV);

            //divide set
            set("DIVS", toB("011101"),RR|IR|RV|IV|VV);

            //divide long
            set("LDIV", toB("011110"),RR|VV);

            //divide long set
            set("LDIVS", toB("011111"),RR|VV);

            //modulus
            set("MOD",toB("100000"),RR|IR|RV|IV|VV);

            //modulus set
            set("MODS", toB("100001"),RR|IR|RV|IV|VV);

            //Logical shift right
            set("LSR", toB("101000"),RR|IR|RV|IV|VV);

            //Logical shift right set
            set("LSRS", toB("101001"),RR|IR|RV|IV|VV);

            //Logical shift left
            set("LSL", toB("101010"),RR|IR|RV|IV|VV);

            //Logical shift left set
            set("LSLS", toB("101011"),RR|IR|RV|IV|VV);

            //Arithmetic shift left
            set("ASL", toB("101100"),RR|IR|RV|IV|VV);

            //Arithmetic shift left set
            set("ASLS",toB("101101"),RR|IR|RV|IV|VV);

            //Arithmetic shift right
            set("ASR", toB("101110"),RR|IR|RV|IV|VV);

            //Arightmetic shift right set
            set("ASRS", toB("101111"),RR|IR|RV|IV|VV);

            //Bitwise and
            set("AND", toB("110000"),RR|IR|RV|IV|VV);

            //Bitwise and set
            set("ANDS", toB("110001"),RR|IR|RV|IV|VV);

            //Bitwise nand
            set("NAND", toB("110010"),RR|IR|RV|IV|VV);

            //Bitwise nand set
            set("NANDS", toB("110011"),RR|IR|RV|IV|VV);

            //Bitwise or
            set("OR", toB("110100"),RR|IR|RV|IV|VV);

            //Bitwise or set
            set("ORS", toB("110101"),RR|IR|RV|IV|VV);

            //Bitwise not or
            set("NOR", toB("110110"),RR|IR|RV|IV|VV);

            //Bitwise not or set
            set("NORS", toB("110111"),RR|IR|RV|IV|VV);

            //Bitwise exclusive or
            set("XOR", toB("111000"),RR|IR|RV|IV|VV);

            //Bitwise exclusive or
            set("XORS", toB("111001"),RR|IR|RV|IV|VV);

            //NOT
            set("NOT", toB("111010"),RR|RV|VV);

            //NOTS
            set("NOTS", toB("111011"),RR|RV|VV);

            //To Integer
            set("TOI",toB("111100"), RR|VV);

            //To float
            set("TOF",toB("111101"), RR |VV);

            set("NOP",toB("000011"), 0);
        }

        ~InstructionResolver(){
            for(InstructionDefinition* def : nameTable.values()){
                delete def;
            }
        }


};
#endif
