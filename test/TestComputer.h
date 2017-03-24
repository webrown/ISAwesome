#ifndef TESTCOMPUTER_H
#define TESTCOMPUTER_H
#include <QtTest/QtTest>
#include <QDebug>
#include "../src/computer/Computer.h"

class TestComputer: public QObject
{
    Q_OBJECT
    public:
        Computer computer;
        Register *regs;
        MainMemory *mem;

    private slots:
        void initTestCase();
        void test_one_add();
        void test_multiple_add_diff_reg();
        void test_multiple_add_same_reg();
        void test_multiple_add_float_reg();
        void test_add_PC();
        void cleanupTestCase();
};
#endif
