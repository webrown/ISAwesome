#ifndef TESTBASELINE_H
#define TESTBASELINE_H
#include <QtTest/QtTest>
#include <QDebug>
#include "../src/memory/Register.h"
#include "../src/memory/MemoryStructure.h"
#include "../src/pipeline/Baseline.h"
#include "../src/memory/Flag.h"
#include "../src/Utility.h"


class TestBaseline: public QObject
{
    Q_OBJECT
    public:
        Register *regs;
        MemoryStructure *mem;
        Baseline *base;

    private slots:
        void load(QVector<uint> in);
        void initTestCase();
        void test_one_add();
        void test_multiple_add_diff_reg();
        void test_multiple_add_same_reg();
        void test_multiple_add_float_reg();
        void test_add_PC();
        void test_snippet();
        void cleanupTestCase();
};
#endif
