#include <QtTest/QtTest>
#include "TestInstructionResolver.h"
#include "TestAssembler.h"
#include "TestComputer.h"

int main(int argc, char *argv[])
{
/*     TestInstructionResolver test1;
 *     QTest::qExec(&test1,argc, argv);
 *
 *     TestAssembler test2;
 *     QTest::qExec(&test2,argc, argv); */

    TestComputer test3;
    QTest::qExec(&test3, argc,argv);


    return 0;
}
