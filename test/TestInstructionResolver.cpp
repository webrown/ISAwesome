#include "TestInstructionResolver.h"
void TestInstructionResolver:: test_parseB(){
    InstructionDefinition* def = resolver.nameTable["B"];
    QVERIFY(def != NULL);
    QVERIFY(def->opcode == 0);
    QVERIFY(def->name == "B");

    //Not enough argument
    QStringList test;
    ParseResult result = def->parse(test);
    QCOMPARE(result.error,QString("Invalid number of arguments"));

    //Too many argument
    test = QStringList();
    test << "1";
    test << "2";
    result = def->parse(test);
    QCOMPARE(result.error,QString("Invalid number of arguments"));

    //Invalid argument
    test = QStringList();
    test << "R11";
    result = def->parse(test);
    QCOMPARE(result.error, QString("Invalid argument"));

    //Valid argument
    test = QStringList();
    test << "11";
    result = def->parse(test);
    QCOMPARE(result.error, QString("None"));
    QVERIFY(result.parsed == 11);
}

void TestInstructionResolver:: test_parseBL(){
    InstructionDefinition* def = resolver.nameTable["BL"];
    QVERIFY(def != NULL);
    QVERIFY(def->opcode == 1);
    QVERIFY(def->name == "BL");

    //Not enough argument
    QStringList test;
    ParseResult result = def->parse(test);
    QCOMPARE(result.error,QString("Invalid number of arguments"));

    //Too many argument
    test = QStringList();
    test << "R1";
    test << "R2";
    result = def->parse(test);
    QCOMPARE(result.error,QString("Invalid number of arguments"));

    //Invalid argument
    test = QStringList();
    test << "11";
    result = def->parse(test);
    QCOMPARE(result.error, QString("Invalid argument"));

    //Invalid argument
    test = QStringList();
    test << "R32";
    result = def->parse(test);
    QCOMPARE(result.error, QString("Invalid argument"));

    //Valid argument
    test = QStringList();
    test << "R5";
    result = def->parse(test);
    QCOMPARE(result.error, QString("None"));
    QVERIFY(result.parsed == 5);

    //Valid argument with warning
    test = QStringList();
    test << "R11";
    result = def->parse(test);
    QCOMPARE(result.error, QString("None"));
    QCOMPARE(result.warning, QString("Float Register?"));
    QVERIFY(result.parsed == 11);
}

void TestInstructionResolver:: test_parseArith(){
    InstructionDefinition* def = resolver.nameTable["CMP"];
    QVERIFY(def != NULL);
    QVERIFY(def->opcode == 3);
    QVERIFY(def->name == "CMP");

    //Not enough argument
    QStringList test;
    ParseResult result = def->parse(test);
    QCOMPARE(result.error,QString("Invalid number of arguments"));
    
    //Not enough argument
    test = QStringList();
    test << "R1";
    result = def->parse(test);
    QCOMPARE(result.error,QString("Invalid number of arguments"));


    //Too many argument
    test = QStringList();
    test << "R1";
    test << "R2";
    test << "R10";
    result = def->parse(test);
    QCOMPARE(result.error,QString("Invalid number of arguments"));

    //Invalid argument
    test = QStringList();
    test << "R21";
    test << "R32";
    result = def->parse(test);
    QCOMPARE(result.error, QString("Invalid argument"));

    //Invalid argument
    test = QStringList();
    test << "R21";
    test << "1";
    result = def->parse(test);
    QCOMPARE(result.error, QString("Invalid argument"));

    //Valid argument
    test = QStringList();
    test << "R5";
    test << "R4";
    result = def->parse(test);
    QCOMPARE(result.error, QString("None"));
    QVERIFY(result.parsed == toB("1000000000000010100100"));

    //Valid argument
    test = QStringList();
    test << "16";
    test << "R4";
    result = def->parse(test);
    QCOMPARE(result.error, QString("None"));
    QVERIFY(result.parsed == toB("0000000000001000000100"));


    //Valid argument with warning
    test = QStringList();
    test << "R11";
    test << "R9";
    result = def->parse(test);
    QCOMPARE(result.error, QString("None"));
    QCOMPARE(result.warning, QString("Type mix warning"));
    QVERIFY(result.parsed == toB("1000000000000101101001"));

}
