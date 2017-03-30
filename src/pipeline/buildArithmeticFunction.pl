#!/usr/bin/perl
use strict;
use warnings;

if(@ARGV != 2) {
    print "I want 2 params:  instruction name (Add) and instruction command (+)\n";
}

my $instructionName = shift;
my $instructionCommand = shift;
my $objectName = "${instructionName}Operation";

my $hFileName = "${objectName}.h";
my $cppFileName = "${objectName}.cpp";

# Never overwrite a file.
die("Delete $hFileName before running this script.") if -e $hFileName;
die("Delete $cppFileName before running this script.") if -e $cppFileName;

open(my $hHandle, '>', $hFileName) or die "Could not open file '$hFileName' $!";
open(my $cppHandle, '>', $cppFileName) or die "Could not open file '$cppFileName' $!";

my $instructionNameCap = uc $instructionName;

print $hHandle "#ifndef ${instructionNameCap}_OPERATION_H
#define ${instructionNameCap}_OPERATION_H
#include \"ArithmeticOperation.h\"
class $objectName : public ArithmeticOperation{
    public:
        static $objectName singleton;
        Value scalarOperation(int a, int b);
        Value scalarOperation(float a, float b);
};
#endif
";

close $hHandle;

print $cppHandle "#include \"$objectName.h\"
#include <QDebug>

$objectName $objectName ::singleton;

Value ${objectName}::scalarOperation(int a, int b){
  Value v;
  v.i = a $instructionCommand b;
  return v;
}

Value ${objectName}::scalarOperation(float a, float b){
  Value v;
  v.f = a $instructionCommand b;
  return v;
}

";

close $cppHandle;
