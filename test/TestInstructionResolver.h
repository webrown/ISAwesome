#ifndef TESTINSTRUCTIONRESOLVER_H
#define TESTINSTRUCTIONRESOLVER_H
#include <QtTest/QtTest>
#include <QDebug>
#include "../src/assembler/InstructionResolver.h"

class TestInstructionResolver: public QObject
{
    Q_OBJECT
    public:
        InstructionResolver resolver;

    private slots:
        void test_parseB(); 
        void test_parseBL();
        void test_parseArith();
};
#endif
