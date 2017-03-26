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
    QVERIFY(regs->read(0).asUInt == 3u);
    base->run();
    QVERIFY(regs->read(0).asUInt == 6u);
    base->stop();
}
/* Add 0 R4
 * Add 1 R3
 * Add 2 R2
 * Add 3 R1 */
void TestBaseline::test_multiple_add_diff_reg(){
    QVector<uint> instructions;
    instructions.append(3825205252u);
    instructions.append(3825205283u);
    instructions.append(3825205314u);
    instructions.append(3825205345u);
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
    QVERIFY(regs->read(11).asFloat == 0.0);
    base->run();
    QVERIFY(regs->read(14).asFloat == 1.0);
    base->run();
    QVERIFY(regs->read(17).asFloat == 2.0);
    base->run();
    QVERIFY(regs->read(12).asFloat == 3.0);
    base->stop(); 
}

//Add 20 PC
void TestBaseline::test_add_PC(){
    QVector<uint> instructions;
    instructions.append(3825205911u);
    load(instructions);

    base->init();
    base->run();
    QVERIFY(regs->read(Register::PC).i == 21);
    base->stop();

}

//B 20
void TestBaseline::test_branch(){
    QVector<uint> instructions;
    instructions.append(3758096404u);
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

void TestBaseline::test_snippet(){
    QVector<uint> instructions;
    instructions.append(3774873857u); //CPY 8 R1 ; Test immediate-scalar int
    instructions.append(3774873925u); //CPY 10 R5
    instructions.append(3785359521u); //STO R5 R1
    instructions.append(3827302433u); //ADD R1 R1 ; 16
    instructions.append(3774873957u); //CPY 11 R5
    instructions.append(3785359521u); //STO R5 R1
    instructions.append(3774874594u); //CPY 31 R2
    instructions.append(3776970831u); //CPY R2 R15 ; Move to floating register coldly
    instructions.append(3961520175u); //AND R1 R15 ;AND noop
    instructions.append(3827302434u); //ADD R1 R2 ; AND int scalar-scalar
    instructions.append(3774873925u); //CPY 10 R5
    instructions.append(3781165240u); //LOD R5 R24
    instructions.append(3781165241u); //LOD R5 R25
    instructions.append(3827303193u); //ADD R24 R25 ; ADD dot
    instructions.append(3825205251u); //ADD R24 R3 ; ADD reduce (like SOE command)
    instructions.append(3774873658u); //CPY 1 R26 ; CPY broadcast immediate
    instructions.append(3810526041u); //ARR R26 R25 ; Grab element 1 everywhere
    instructions.append(3772777241u); //CMP R24 R25
    instructions.append(285212730u); //NE CMP 1 R26 ; Standard flag extraction
    instructions.append(3770679301u);//CMP 0 R5
    instructions.append(42u); //EQ B 42 ; Was this the syntax we settled on for conditions?
    
    load(instructions);

    base->init();
    base->run();
    QVERIFY(regs->read(1).asUInt == 8u);
    base->run();
    QVERIFY(regs->read(5).asUInt == 10u);
    base->run();
    QVERIFY(mem->_mainMemory->read(10)->at(0).asUInt == 8u);
    base->run();
    QVERIFY(regs->read(1).asUInt == 16u);
    base->run();
    QVERIFY(regs->read(5).asUInt == 11u);
    base->run();
    base->run();
    QVERIFY(regs->read(2).asUInt == 31u);    
    base->run();
    QVERIFY(regs->read(15).asUInt == 31u);    //AND R1 R15 ;AND noop
    base->run();
    QVERIFY(regs->read(15).asUInt == (16&31));    //ADD R1 R2 ; AND int scalar-scalar

     base->run();
    QVERIFY(regs->read(2).asUInt == 47u);    
     base->run();
    QVERIFY(regs->read(5).asUInt == 10u);    
     base->run();
    QVector<Value> v = regs->readVector(24);
     for(int i =0; i < 64; i++){
        QVERIFY(v[i].asUInt == 8u);     
     }
     base->run();
     v = regs->readVector(24);
     for(int i =0; i < 64; i++){
        QVERIFY(v[i].asUInt == 8u);     
     }
     base->run();
     v =  regs->readVector(25);
     for(int i =0; i < 64; i++){
         QVERIFY(v[i].asUInt == 16u);     
     }
     base->run();
    QVERIFY(regs->read(3).asUInt == 512u);     

     base->run();

        v =  regs->readVector(26);
     for(int i =0; i < 64; i++){
         QVERIFY(v[i].asUInt == 1u);     
     } 
     base->run();
        v =  regs->readVector(25);
     for(int i =0; i < 64; i++){
         QVERIFY(v[i].asUInt == 1u);     
     } 
     base->run();

     v = regs->_flags;
     QBitArray b = Flag::has(v, Flag::NE);
     for(int i =0; i < 64; i++){
         QVERIFY(b[i]);     
     }
     base->run();
        v =  regs->readVector(26);
     for(int i =0; i < 64; i++){
         QVERIFY(v[i].asUInt == 1u);     
     } 
     base->run();
    QVERIFY(Flag::has(regs->_flag, Flag::NE));     
    base->run();
    QVERIFY(regs->getPC() == 42u);
    base->stop(); 
}
