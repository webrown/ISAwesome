#ifndef INSTRUCTIONRESOLVER_H
#define INSTRUCTIONRESOLVER_H
#include <QMap>

enum ArgumentType{
  I = 1,
  I22 = 2,
  R = 4,
  V = 8
  IR = 16,
  IV = 32,
  RR = 64,
  RV = 128,
  VR = 256,
  VV = 512,
  RVI = 1024,
  RVR = 2048,
  VIR = 4096,
  VRR = 8192
}


class InstructionResolver{
  public:
    const QMap<QString, uint> nameMap;
    const QMap<uint, QString> opcodeMap;
    const QMap<uint, Instruction> instructionMap;

    InstructionResolver(){
      nameMap.insert("B", 0);
    }
};
#endif
