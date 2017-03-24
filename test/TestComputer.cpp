#include "TestComputer.h"

void TestComputer::initTestCase(){
    regs = computer.regs;
    mem = computer.mems->_mainMemory;
    //Do nothing
}
//Add 0 R0
void TestComputer::test_one_add(){
    QVector<uint>* instructions =  new QVector<uint>();
    instructions->append(3825205248u);
    computer.init(instructions);
    computer.step(1);
    QVERIFY(regs->r(0).asUInt == 0u);
    computer.stop();
}

/* Add 0 R0
 * Add 1 R0
 * Add 2 R0
 * Add 3 R0 */
void TestComputer::test_multiple_add_same_reg(){
    QVector<uint>* instructions =  new QVector<uint>();
    instructions->append(3825205248u);
    instructions->append(3825205280u);
    instructions->append(3825205312u);
    instructions->append(3825205344u);

    computer.init(instructions);
    computer.step(1);
    QVERIFY(regs->r(0).asUInt == 0u);
    computer.step(1);
    QVERIFY(regs->r(0).asUInt == 1u);
    computer.step(1);
    QVERIFY(regs->r(0).asUInt == 2u);
    computer.step(1);
    QVERIFY(regs->r(0).asUInt == 3u);
    computer.stop();
}
/* Add 0 R4
 * Add 1 R3
 * Add 2 R2
 * Add 3 R1 */
void TestComputer::test_multiple_add_diff_reg(){
    QVector<uint>* instructions =  new QVector<uint>();
    instructions->append(3825205248u);
    instructions->append(3825205280u);
    instructions->append(3825205312u);
    instructions->append(3825205344u);

    computer.init(instructions);
    computer.step(1);
    QVERIFY(regs->r(4).asUInt == 0u);
    computer.step(1);
    QVERIFY(regs->r(3).asUInt == 1u);
    computer.step(1);
    QVERIFY(regs->r(2).asUInt == 2u);
    computer.step(1);
    QVERIFY(regs->r(1).asUInt == 3u);
    computer.stop(); 
}
/* Add 0 R11
 * Add 1 R14
 * Add 2 R17
 * Add 3 R12 */
void TestComputer::test_multiple_add_float_reg(){
    QVector<uint>* instructions =  new QVector<uint>();
    instructions->append(3825205259u);
    instructions->append(3825205294u);
    instructions->append(3825205329u);
    instructions->append(3825205356u);

    computer.init(instructions);
    computer.step(1);
    QVERIFY(regs->r(11).asUInt == 0u);
    computer.step(1);
    QVERIFY(regs->r(14).asUInt == 1u);
    computer.step(1);
    QVERIFY(regs->r(17).asUInt == 2u);
    computer.step(1);
    QVERIFY(regs->r(12).asUInt == 3u);
    computer.stop(); 
}

//Add 20 PC
void TestComputer::test_add_PC(){
QVector<uint>* instructions =  new QVector<uint>();
    instructions->append(3825205911u);
    computer.init(instructions);
    computer.step(1);
    QVERIFY(regs->r(Register::PC).asUInt == 20u);
    computer.stop();

}

void TestComputer::cleanupTestCase(){
    //Do nothing
}
