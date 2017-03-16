#include "InstructionResolver.h"

QRegExp intReg("^R([0-9]|2[0-3])$");
QRegExp floatReg("^R1[0-9]$");
QRegExp intVec("^R2[4-7]$");
QRegExp floatVec("^(R28|R29|R30|R31)$"); 

bool _checkSize(QStringList tokens, ParseResult* result, int size){
    if(tokens.size() != size){
        result->failureLocation = tokens.size();
        result->error = "Invalid number of arguments";
        return false;
    }
    return true;
}
bool _parse(QStringList tokens, ParseResult* result, QRegExp srcI, QRegExp srcF, QRegExp destI, QRegExp destF){
    short statusI;
    short statusF;
    statusI = srcI.exactMatch(tokens[0])  + destI.exactMatch(tokens[1]);
    statusF = srcF.exactMatch(tokens[0])  + destF.exactMatch(tokens[1]);
    if(statusI + statusF < 2){
        return false;
    } if(statusI == 1 && statusF == 1){ result->warning = "Type mix warning";
        result->failureLocation = 1;
    }
    uint src= tokens[0].remove(0,1).toInt();
    uint dest =tokens[1].remove(0,1).toInt();
    result->parsed = (((1 << 16) | src) << 5) |dest;
    return true;
}
bool _parse2(QStringList tokens, ParseResult* result, QRegExp destI, QRegExp destF){
    bool ok;
    uint src = tokens[0].toInt(&ok);
    if(ok == false && src >= ( 1<< 17)){
        return false;
    }
    if(destI.exactMatch(tokens[1])){
        //Do nothing
    }
    else if(destF.exactMatch(tokens[1])){
        result->warning = "Type mix warning";
        result->failureLocation = 1;
    }
    else{
        return false;
    }
    uint dest =tokens[1].remove(0,1).toInt();
    result->parsed = (src << 5) |dest;
    return true;
}
bool RR(QStringList tokens, ParseResult* result){
    return _parse(tokens, result, intReg, floatReg, intReg, floatReg);
}
bool RV(QStringList tokens, ParseResult* result){
    return _parse(tokens, result, intReg, floatReg, intVec, floatVec);
}
bool VR(QStringList tokens, ParseResult* result){
    return _parse(tokens, result, intVec, floatVec, intReg, floatReg);
}
bool VV(QStringList tokens, ParseResult* result){
    return _parse(tokens, result, intVec, floatVec, intVec, floatVec);
}
bool IR(QStringList tokens, ParseResult* result){
    return _parse2(tokens, result,intReg, floatReg);
}
bool IV(QStringList tokens, ParseResult* result){
    return _parse2(tokens, result,intVec, floatVec);
}

ParseResult parseArith1(QStringList tokens){
    ParseResult result;
    if(_checkSize(tokens, &result, 2) == false){
        return result;
    }
    if(RR(tokens, &result)) ;
    else if(IR(tokens, &result)) ;
    else if(RV(tokens, &result)) ;
    else if(IV(tokens, &result)) ; 
    else if(VV(tokens, &result)) ;
    else{
        result.error = "Invalid argument";
        result.failureLocation = 1;
    }
    return result;

}

ParseResult parseArith2(QStringList tokens){
    ParseResult result;
    if(_checkSize(tokens, &result, 2) == false){
        return result;
    }
    if(RR(tokens, &result)) ;
    else if(VV(tokens, &result)) ;
    else{
        result.error = "Invalid argument";
        result.failureLocation = 1;
    }
    return result;

}

ParseResult parseVR(QStringList tokens){
    ParseResult result;
    if(_checkSize(tokens, &result, 2) == false){
        return result;
    }
    if(VR(tokens, &result)) ;
    else{
        result.error = "Invalid argument";
        result.failureLocation = 1;
    }
    return result;
}
ParseResult parseMVX(QStringList tokens){
    ParseResult result;
    if(_checkSize(tokens, &result, 2) == false){
        return result;
    }
    if(RV(tokens, &result)) ;
    else if(IV(tokens, &result)) ; 
    else if(VV(tokens, &result)) ;
    else{
        result.error = "Invalid argument";
        result.failureLocation = 1;
    }
    return result;
}
ParseResult parseARR(QStringList tokens){
    ParseResult result;
    if(_checkSize(tokens, &result, 2) == false){
        return result;
    }
    if(RV(tokens, &result)) ;
    if(VV(tokens, &result)) ;
    else{
        result.error = "Invalid argument";
        result.failureLocation = 1;
    }
    return result;
}

ParseResult parseSTO(QStringList tokens){
    ParseResult result;
    if(_checkSize(tokens, &result, 2) == false){
        return result;
    }
    if(RR(tokens, &result)) ;
    else if(VR(tokens, &result)) ;
    else{
        result.error = "Invalid argument";
        result.failureLocation = 1;
    }
    return result;

}
ParseResult parseLOD(QStringList tokens){
    ParseResult result;
    if(_checkSize(tokens, &result, 2) == false){
        return result;
    }
    if(RR(tokens, &result)) ;
    else if(RV(tokens, &result)) ;
    else{
        result.error = "Invalid argument";
        result.failureLocation = 1;
    }
    return result;

}

ParseResult parseCPY(QStringList tokens){
    ParseResult result;
    if(_checkSize(tokens, &result, 2) == false){
        return result;
    }
    if(IR(tokens, &result)) ;
    else if(RR(tokens, &result)) ;
    else if(VV(tokens, &result)) ;
    else if(RV(tokens, &result)) ; 
    else{
        result.error = "Invalid argument";
        result.failureLocation = 1;
    }
    return result;

}

ParseResult parseB(QStringList tokens){
    ParseResult result;
    if(_checkSize(tokens, &result, 1) == false){
        return result;
    }
    bool okay;
    result.parsed = tokens[0].toInt(&okay, 10);
    if(okay == false || result.parsed >= (1<<23)){
        result.failureLocation = 1;
        result.error = "Invalid argument";
    }
    return result;
}
ParseResult parseBL(QStringList tokens){
    ParseResult result;
    if(_checkSize(tokens, &result, 1) == false){
        return result;
    }
    if(intReg.exactMatch(tokens[0])){
        //do nothing
    }
    else if(floatReg.exactMatch(tokens[0])){
        result.failureLocation = 1;
        result.warning = "Float Register?";
    }
    else{
        result.failureLocation = 1;
        result.error = "Invalid argument";
        return result;
    }
    tokens[0].remove(0,1);
    result.parsed = tokens[0].toInt();

    return result;
}

#define L_BIT toB("1000000000000000000000")
ParseResult unparseB(uint args){
    ParseResult result;
    result.unparsed = "0X" + QString::number(args, 16);
    return result;
}

ParseResult unparseBL(uint args){
    ParseResult result;
    result.unparsed = "R" + QString::number((args & ((1<<5)-1)));
    return result;
}

ParseResult unparseUnary(uint args){
    ParseResult result;
    //register
    if((args & L_BIT) == L_BIT){
        result.unparsed = "R" + QString::number((args & ((1<<5)-1)));
    }
    //immediate
    else{
        result.unparsed = "#0X" +QString::number((args & !L_BIT),16);
    }
    return result;
}

ParseResult unparseBinary(uint args){
    ParseResult result;
    uint firstArg = ((args & !L_BIT)& !((1<<5)-1)) >> 5;
    //register
    
    if((args & L_BIT) == L_BIT){
        result.unparsed = "R" + QString::number(firstArg & ((1<<5)-1),16) + " ";
    }
    //immediate
    else{
        result.unparsed = "#0X" + QString::number(firstArg,16) + " ";
    }
    result.unparsed += " R" + QString::number((args & ((1<<5)-1)));

    return result;

}

InstructionResolver::InstructionResolver(){

    // Branch
    set("B", 0x0, parseB, unparseB);

    // Branch with register
    set("BL", 0x1, parseBL, unparseBL);

    // Compare
    set("CMP",0x3, parseArith1, unparseBinary);

    // CPY
    set("CPY", 0x4, parseCPY, unparseBinary);

    // LOD
    set("LOD", 0x5, parseLOD,unparseBinary);

    // STO
    set("STO", 0x6, parseSTO,unparseBinary);

    // RVE
    // set("RVE",0x8,VIR|VRR);

    // Write vector
    // set("WVE",0x9,RVR |RVI);

    //Move down
    set("MVD",0xA,parseMVX, unparseBinary);

    //Move Up
    set("MVU",0xB,parseMVX, unparseBinary);

    //Arrange
    set("ARR",0xC,parseARR, unparseBinary);

    //Sequence
    // set("SEQ",0xD,V);
    //Mulptiply elements
    set("MOE",0xE,parseVR, unparseBinary);

    //Sum elements
    set("SOE",0XF,parseVR, unparseBinary);

    //Add
    set("ADD", toB("010000"),parseArith1, unparseBinary);

    //ADDS
    set("ADDS",toB("010001"),parseArith1, unparseBinary);

    //ADC
    set("ADC", toB("010010"),parseArith2, unparseBinary);

    //ADCS
    set("ADCS",toB("010011"),parseArith2, unparseBinary);

    //Subtract
    set("SUB",toB("010100"),parseArith1, unparseBinary);

    //Subtract set
    set("SUBS",toB("010101"),parseArith1, unparseBinary);

    //Subtract carry
    set("SBC",toB("010110"),parseArith2, unparseBinary);

    //Subtract carry set
    set("SBCS",toB("010111"),parseArith2, unparseBinary);

    //Multiply
    set("MUL",toB("011000"),parseArith1, unparseBinary);

    //Multiply set
    set("MULS", toB("011001"),parseArith1, unparseBinary);

    //Long multiply
    set("LMUL", toB("011010"),parseArith2, unparseBinary);

    //Long multiply set
    set("LMULS",toB("011011"),parseArith2, unparseBinary);

    //divide
    set("DIV", toB("011100"),parseArith1, unparseBinary);

    //divide set
    set("DIVS", toB("011101"),parseArith1, unparseBinary);

    //divide long
    set("LDIV", toB("011110"),parseArith2, unparseBinary);

    //divide long set
    set("LDIVS", toB("011111"),parseArith2, unparseBinary);

    //modulus
    set("MOD",toB("100000"),parseArith1, unparseBinary);

    //modulus set
    set("MODS", toB("100001"),parseArith1, unparseBinary);

    //Logical shift right
    set("LSR", toB("101000"),parseArith1, unparseBinary);

    //Logical shift right set
    set("LSRS", toB("101001"),parseArith1, unparseBinary);

    //Logical shift left
    set("LSL", toB("101010"),parseArith1, unparseBinary);

    //Logical shift left set
    set("LSLS", toB("101011"),parseArith1, unparseBinary);

    //Arithmetic shift left
    set("ASL", toB("101100"),parseArith1, unparseBinary);

    //Arithmetic shift left set
    set("ASLS",toB("101101"),parseArith1, unparseBinary);

    //Arithmetic shift right
    set("ASR", toB("101110"),parseArith1, unparseBinary);

    //Arightmetic shift right set
    set("ASRS", toB("101111"),parseArith1, unparseBinary);

    //Bitwise and
    set("AND", toB("110000"),parseArith1, unparseBinary);

    //Bitwise and set
    set("ANDS", toB("110001"),parseArith1, unparseBinary);

    //Bitwise nand
    set("NAND", toB("110010"),parseArith1, unparseBinary);

    //Bitwise nand set
    set("NANDS", toB("110011"),parseArith1, unparseBinary);

    //Bitwise or
    set("OR", toB("110100"),parseArith1, unparseBinary);

    //Bitwise or set
    set("ORS", toB("110101"),parseArith1, unparseBinary);

    //Bitwise not or
    set("NOR", toB("110110"),parseArith1, unparseBinary);

    //Bitwise not or set
    set("NORS", toB("110111"),parseArith1, unparseBinary);

    //Bitwise exclusive or
    set("XOR", toB("111000"),parseArith1, unparseBinary);

    //Bitwise exclusive or
    set("XORS", toB("111001"),parseArith1, unparseBinary);

    //NOT
    set("NOT", toB("111010"),parseArith2, unparseBinary);

    //NOTS
    set("NOTS", toB("111011"),parseArith2,unparseBinary);

    //To Integer
    set("TOI",toB("111100"), parseArith2, unparseBinary);

    //To float
    set("TOF",toB("111101"), parseArith2, unparseBinary );
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
