#include <QtTest/QtTest>

class TestInstructionResolver: public QObject
{
    Q_OBJECT
        private slots:
        void dummy(); 
};

void TestInstructionResolver:: dummy(){
    QString str = "Hello";
    QCOMPARE(str.toUpper(), QString("HELLO"));
}

QTEST_MAIN(TestInstructionResolver)
#include "TestInstructionResolver.moc"
