#include "Baseline.h"
#include "spliceMachineCode.h"
Baseline::Baseline(Register *registers, MemoryStructure *memory){
    _registers = registers;
    _memory = memory;
}

Baseline::~Baseline(){
}

void Baseline::init(void){
    // Doesn't really do anything yet
}

void Baseline::run(void){
    // Complete 1 instruction
    QueryResult *qr = NULL;

    // Get the next instruction address.
    qr = registers->read(Register::PC);
    int pc = qr->result.at(0).i;
    delete qr;
    // Get next instruction from memory.
    qr = memory->read(pc);
    unsigned int nextInstruction = qr->result.at(0).asUInt;
    delete qr;
    // Move to next instruction address.
    pc++;
    // What is instruction type?
    int instructionIndex = spliceMachineCode(nextInstruction, 22, 27);
    Instruction instructionType;

B toB(QString("000000")
BL toB(QString("000001")
CMP toB(QString("000010")
CPY toB(QString("000100")
LOD toB(QString("000101")
STO toB(QString("000110")
RVE toB(QString("001000")
WVE toB(QString("001001")
MVD toB(QString("001010")
MVU toB(QString("001011")
ARR toB(QString("001100")
SEQ toB(QString("001101")
SOE toB(QString("001110")
MOE toB(QString("001111")
ADD toB(QString("010000")
ADDS toB(QString("010001")
ADC toB(QString("010010")
ADCS toB(QString("010011")
SUB toB(QString("010100")
SUBS toB(QString("010101")
SBC toB(QString("010110")
SBCS toB(QString("010111")
MUL toB(QString("011000")
MULS toB(QString("011001")
LMUL toB(QString("011010")
LMULS toB(QString("011011")
DIV toB(QString("011100")
DIVS toB(QString("011101")
LDIV toB(QString("011110")
LDIV toB(QString("011111")
MOD toB(QString("100000")
MODS toB(QString("100001")
LSR toB(QString("101000")
LSRS toB(QString("101001")
LSL toB(QString("101010")
LSLS toB(QString("101011")
ASL toB(QString("101100")
ASLS toB(QString("101101")
ASR toB(QString("101110")
ASRS toB(QString("101111")
AND toB(QString("110000")
ANDS toB(QString("110001")
NAND toB(QString("110010")
NANDS toB(QString("110011")
OR toB(QString("110100")
ORS toB(QString("110101.")
NOR toB(QString("110110")
NORS toB(QString("110111")
XOR toB(QString("111000")
XORS toB(QString("111001")
NOT toB(QString("111010")
NOTS toB(QString("111011")
TOI toB(QString("111100")
TOF toB(QString("111101")

    // What is the flag?
    Conditional flag = 
    EQ,
    NE,
    CS,
    CC,
    MI,
    PL,
    VS,
    VC,
    DZ,
    NZ,
    LE,
    GE,
    LT,
    GT,
    AL,
    UN

    // Do what the instruction tells you to.
    // pc is now determined fully.
    registers->write(pc+1, Register::PC);
}

void Baseline::stop(void){
    // Scrub everything.
    // TODO
}

