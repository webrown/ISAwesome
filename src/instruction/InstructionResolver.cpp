#include "InstructionResolver.h"

QRegExp intReg("^R([0-9]|2[0-3])$");
QRegExp floatReg("^R1[0-9]$");
QRegExp intVec("^R2[4-7]$");
QRegExp floatVec("^(R28|R29|R30|R31)$"); 


ParseResult parseB(QStringList tokens){
    ParseResult result;
    if(tokens.size() > 1 || tokens.size() == 0){
        result.failureLocation = tokens.size();
        result.error = "Branch instruction only require 1 operands";
        return result;
    }
    bool okay;
    result.parsed = tokens[0].toInt(&okay, 10);
    if(okay == false && result.parsed >= (1<<23)){
        result.failureLocation = 1;
        result.error = "Branch instruction requires immediate 22";
    }
    return result;
}


ParseResult parseBL(QStringList tokens){
    ParseResult result;
    if(tokens.size() > 1 || tokens.size() == 0){
        result.failureLocation = tokens.size();
        result.error = "Branch instruction only require 1 operands";
        return result;
    }
    if(intReg.exactMatch(tokens[0])){
        //do nothing
    }
    else if(floatReg.exactMatch(tokens[0])){
        result.failureLocation = 1;
        result.warning = "Branch prefers integer register";
    }
    else{
        result.failureLocation = 1;
        result.error = "Branch with Register requires register";
        return result;
    }
    tokens[0].remove("R");
    result.parsed = tokens[0].toInt();

    return result;
}

bool _parseRR(QStringList tokens, ParseResult* result){
    short status;
    status = intReg.exactMatch(tokens[0]) *8 + intReg.exactMatch(tokens[1]) * 4;
    status = floatReg.exactMatch(tokens[0]) * 2 + floatReg.exactMatch(tokens[1]);
    if(status == 0){
        return false;
    }
    if(status == 9 || status == 6){
        result->warning = "Mix use of float and integer";
        result->failureLocation = 1;
    }
    tokens[0].remove("R");
    tokens[1].remove("R");
    //build RR
}
InstructionResolver::InstructionResolver(){

    // Branch
    set("B", 0x0, parseB, NULL);

    // Branch with register
    set("BL", 0x1, parseBL, NULL);

    /*             // Compare
     *             set("CMP",0x3, RR|IR|RV|IV|VV);
     *
     *             // CPY
     *             set("CPY", 0x4, IR|RR|VV|RV);
     *
     *             // LOD
     *             set("LOD", 0x5, RR|RV);
     *
     *             // STO
     *             set("STO", 0x6, RR|VR);
     *
     *             // RVE
     *             set("RVE",0x8,VIR|VRR);
     *
     *             // Write vector
     *             set("WVE",0x9,RVR |RVI);
     *
     *             //Move down
     *             set("MVD",0xA,VV|RV|IV);
     *
     *             //Move Up
     *             set("MVU",0xB,VV|RV|IV);
     *
     *             //Arrange
     *             set("ARR",0xC,VV);
     *
     *             //Sequence
     *             set("SEQ",0xD,V);
     *             //Mulptiply elements
     *             set("MOE",0xE,VR);
     *
     *             //Sum elements
     *             set("SOE",0XF,VR);
     *
     *             //Add
     *             set("ADD", toB("010000"),RR|IR|RV|IV|VV);
     *
     *             //ADDS
     *             set("ADDS",toB("010001"),RR|IR|RV|IV|VV);
     *
     *             //ADC
     *             set("ADC", toB("010010"),RR|VV);
     *
     *             //ADCS
     *             set("ADCS",toB("010011"),RR|VV);
     *
     *             //Subtract
     *             set("SUB",toB("010100"),RR|IR|RV|IV|VV);
     *
     *             //Subtract set
     *             set("SUBS",toB("010101"),RR|IR|RV|IV|VV);
     *
     *             //Subtract carry
     *             set("SBC",toB("010110"),RR|VV);
     *
     *             //Subtract carry set
     *             set("SBCS",toB("010111"),RR|VV);
     *
     *             //Multiply
     *             set("MUL",toB("011000"),RR|IR|RV|IV|VV);
     *
     *             //Multiply set
     *             set("MULS", toB("011001"),RR|IR|RV|IV|VV);
     *
     *             //Long multiply
     *             set("LMUL", toB("011010"),RR|VV);
     *
     *             //Long multiply set
     *             set("LMULS",toB("011011"),RR|VV);
     *
    *             //divide
        *             set("DIV", toB("011100"),RR|IR|RV|IV|VV);
    *
        *             //divide set
        *             set("DIVS", toB("011101"),RR|IR|RV|IV|VV);
    *
        *             //divide long
        *             set("LDIV", toB("011110"),RR|VV);
    *
        *             //divide long set
        *             set("LDIVS", toB("011111"),RR|VV);
    *
        *             //modulus
        *             set("MOD",toB("100000"),RR|IR|RV|IV|VV);
    *
        *             //modulus set
        *             set("MODS", toB("100001"),RR|IR|RV|IV|VV);
    *
        *             //Logical shift right
        *             set("LSR", toB("101000"),RR|IR|RV|IV|VV);
    *
        *             //Logical shift right set
        *             set("LSRS", toB("101001"),RR|IR|RV|IV|VV);
    *
        *             //Logical shift left
        *             set("LSL", toB("101010"),RR|IR|RV|IV|VV);
    *
        *             //Logical shift left set
        *             set("LSLS", toB("101011"),RR|IR|RV|IV|VV);
    *
        *             //Arithmetic shift left
        *             set("ASL", toB("101100"),RR|IR|RV|IV|VV);
    *
        *             //Arithmetic shift left set
        *             set("ASLS",toB("101101"),RR|IR|RV|IV|VV);
    *
        *             //Arithmetic shift right
        *             set("ASR", toB("101110"),RR|IR|RV|IV|VV);
    *
        *             //Arightmetic shift right set
        *             set("ASRS", toB("101111"),RR|IR|RV|IV|VV);
    *
        *             //Bitwise and
        *             set("AND", toB("110000"),RR|IR|RV|IV|VV);
    *
        *             //Bitwise and set
        *             set("ANDS", toB("110001"),RR|IR|RV|IV|VV);
    *
        *             //Bitwise nand
        *             set("NAND", toB("110010"),RR|IR|RV|IV|VV);
    *
        *             //Bitwise nand set
        *             set("NANDS", toB("110011"),RR|IR|RV|IV|VV);
    *
        *             //Bitwise or
        *             set("OR", toB("110100"),RR|IR|RV|IV|VV);
    *
        *             //Bitwise or set
        *             set("ORS", toB("110101"),RR|IR|RV|IV|VV);
    *
        *             //Bitwise not or
        *             set("NOR", toB("110110"),RR|IR|RV|IV|VV);
    *
        *             //Bitwise not or set
        *             set("NORS", toB("110111"),RR|IR|RV|IV|VV);
    *
        *             //Bitwise exclusive or
        *             set("XOR", toB("111000"),RR|IR|RV|IV|VV);
    *
        *             //Bitwise exclusive or
        *             set("XORS", toB("111001"),RR|IR|RV|IV|VV);
    *
        *             //NOT
        *             set("NOT", toB("111010"),RR|RV|VV);
    *
        *             //NOTS
        *             set("NOTS", toB("111011"),RR|RV|VV);
    *
        *             //To Integer
        *             set("TOI",toB("111100"), RR|VV);
    *
        *             //To float
        *             set("TOF",toB("111101"), RR |VV);
    */
        set("NOP",toB("000011"), NULL, NULL); 
}
InstructionResolver::~InstructionResolver(){
    for(InstructionDefinition* def : nameTable.values()){
        delete def;
    }
}

void InstructionResolver:: set(QString name, uint opcode, ParseResult (*parseFunc)(QStringList), ParseResult (*unparseFunc)(uint)){
    InstructionDefinition* inst = new InstructionDefinition(name, opcode, parseFunc, unparseFunc);
    nameTable[name] = inst;
    opcodeTable[opcode] = inst;
}
