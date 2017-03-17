#ifndef CONDITIONRESOLVER_H
#define CONDITIONRESOLVER_H
#include <QMap>
#include "../Utility.h"



class ConditionResolver{
  public:
    QMap<QString, uint> nameTable;
    QMap<uint, QString> condTable;
//    const QTable<uint, Instruction> instructionTable;
    void set(QString name, uint cond){
      nameTable[name] = cond;
      condTable[cond] = name;
    }

    ConditionResolver(){
      set("EQ", toB("0000"));
      set("NE", toB("0001"));
      set("CS", toB("0010"));
      set("CC", toB("0011"));
      set("MI", toB("0100"));
      set("PL", toB("0101"));
      set("VS", toB("0110"));
      set("VC", toB("0111"));
      set("DZ", toB("1000"));
      set("NZ", toB("1001"));
      set("LE", toB("1010"));
      set("GE", toB("1011"));
      set("LT", toB("1100"));
      set("GT", toB("1101"));
      set("AL", toB("1110"));
      set("UN", toB("1111"));


    }

};
#endif
