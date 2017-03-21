#ifndef TESTASSEMBLER_H
#define TESTASSEMBLER_H
#include <QtTest/QtTest>
#include <QDebug>
#include "../src/assembler/Assembler.h"

class TestAssembler: public QObject
{
    Q_OBJECT
    public:
        Assembler assembler;

    private slots:
        void test_simple();
};
#endif
