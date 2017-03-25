#include "TestBaseline.h"

void TestBaseline::initTestCase(){
    regs = new Register();
    mem = new MemoryStructure(MAIN_MEMORY_DELAY);
    base = new Baseline(regs,mem);
}
void TestBaseline::load(QVector<uint> in){
    QVector<Value>* instructions = new QVector<Value>();
    for(int i =0; i < in.size(); i++){
        Value v = {in[i]};
        instructions->append(v);
    }
    mem->_mainMemory->write(instructions, 0u);
}

//Add 0 R0
void TestBaseline::test_one_add(){
    QVector<uint> instructions;
    instructions.append(3825205248u);
    load(instructions);

    base->init();
    base->run();
    QVERIFY(regs->read(0).asUInt == 0u);
    base->stop();
}

/* Add 0 R0
 * Add 1 R0
 * Add 2 R0
 * Add 3 R0 */
void TestBaseline::test_multiple_add_same_reg(){
    QVector<uint> instructions;
    instructions.append(3825205248u);
    instructions.append(3825205280u);
    instructions.append(3825205312u);
    instructions.append(3825205344u);
    load(instructions);

    base->init();
    base->run();
    QVERIFY(regs->read(0).asUInt == 0u);
    base->run();
    QVERIFY(regs->read(0).asUInt == 1u);
    base->run();
    QVERIFY(regs->read(0).asUInt == 2u);
    base->run();
    QVERIFY(regs->read(0).asUInt == 3u);
    base->stop();
}
/* Add 0 R4
 * Add 1 R3
 * Add 2 R2
 * Add 3 R1 */
void TestBaseline::test_multiple_add_diff_reg(){
    QVector<uint> instructions;
    instructions.append(3825205248u);
    instructions.append(3825205280u);
    instructions.append(3825205312u);
    instructions.append(3825205344u);
    load(instructions);

    base->init();
    base->run();
    QVERIFY(regs->read(4).asUInt == 0u);
    base->run();
    QVERIFY(regs->read(3).asUInt == 1u);
    base->run();
    QVERIFY(regs->read(2).asUInt == 2u);
    base->run();
    QVERIFY(regs->read(1).asUInt == 3u);
    base->stop(); 
}
/* Add 0 R11
 * Add 1 R14
 * Add 2 R17
 * Add 3 R12 */
void TestBaseline::test_multiple_add_float_reg(){
    QVector<uint> instructions;
    instructions.append(3825205259u);
    instructions.append(3825205294u);
    instructions.append(3825205329u);
    instructions.append(3825205356u);
    load(instructions);

    base->init();
    base->run();
    QVERIFY(regs->read(11).asUInt == 0u);
    base->run();
    QVERIFY(regs->read(14).asUInt == 1u);
    base->run();
    QVERIFY(regs->read(17).asUInt == 2u);
    base->run();
    QVERIFY(regs->read(12).asUInt == 3u);
    base->stop(); 
}

//Add 20 PC
void TestBaseline::test_add_PC(){
    QVector<uint> instructions;
    instructions.append(3825205911u);
    load(instructions);

    base->init();
    base->run();
    QVERIFY(regs->read((int)Register::PC).asUInt == 20u);
    base->stop();

}

void TestBaseline::cleanupTestCase(){
    delete regs;
    delete mem;
    delete base;
}
