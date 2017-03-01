#include <iostream>
#include "assembler.h" 
#include <QVector> 
#include <QtDebug>
#include <QTime>
#include "../architecture.h"
#include "../instruction/instructionResolver.h"

Assembler::Assembler(){
  if(Assembler::isExisting == true){
    qDebug() << "Assembler already exists!" <<endl;
    exit(-1);
  }

  qDebug() << "Assembler initialized." <<endl;
  Assembler::isExisting = true;
}

Assembler::~Assembler(){
  clear();
}

void Assembler::init(){
  qDebug() << "Initiating Assembler" << endl;
  _success = true;
  uint mainAddress = 0;
  
  _labelTable = new QMap<QString, uint>();
  _aliasTable = new QMap<QString, QString>();

  _errorLog = new QList<Error>();
  _warningLog = new QList<Warning>();

  _preprocessedQueue = new QList<Preprocessed>();
  _instructions = new QVector<uint>();
  _addresses = new QVector<uint>();
}

void Assembler::clear(){
  qDebug() << "Cleaning..." <<endl;

  if(_labelTable != NULL){
    delete _labelTable;
  }
  if(_aliasTable != NULL){
    delete _aliasTable;
  }

  _errorLog = NULL;
  _warningLog = NULL;
  if(_preprocessedQueue != NULL){
    delete _preprocessedQueue;
  }
  _instructions = NULL;
  _addresses = NULL;
}

void Assembler::loadGlobalAlias(){
  qDebug() << "Loading global alias" << endl;

  _aliasTable->insert("LR","R20");
  _aliasTable->insert("SP","R21");
  _aliasTable->insert("BP","R22");
  _aliasTable->insert("PC","R23");
   
  _aliasTable->insert("I0","R0");
  _aliasTable->insert("I1","R1");
  _aliasTable->insert("I2","R2");
  _aliasTable->insert("I3","R3");
  _aliasTable->insert("I4","R4");
  _aliasTable->insert("I5","R5");
  _aliasTable->insert("I6","R6");
  _aliasTable->insert("I7","R7");
  _aliasTable->insert("I8","R8");
  _aliasTable->insert("I9","R9");

  _aliasTable->insert("I0","R10");
  _aliasTable->insert("I1","R11");
  _aliasTable->insert("I2","R12");
  _aliasTable->insert("I3","R13");
  _aliasTable->insert("I4","R14");
  _aliasTable->insert("I5","R15");
  _aliasTable->insert("I6","R16");
  _aliasTable->insert("I7","R17");
  _aliasTable->insert("I8","R18");
  _aliasTable->insert("I9","R19");

  _aliasTable->insert("V0","R24");
  _aliasTable->insert("V1","R25");
  _aliasTable->insert("V2","R26");
  _aliasTable->insert("V3","R27");
  _aliasTable->insert("V4","R28");
  _aliasTable->insert("V5","R29");
  _aliasTable->insert("V6","R30");
  _aliasTable->insert("V7","R31");
}

Assembled* Assembler::assemble(QStringList documents){
  //Start time to measure how long it took to compile
  QTime timer;
  timer.start();

  qDebug() << "----------Start Assembly-------------" << endl;

  //initialize assembler
  init();

  //load gloval alias such register name
  loadGlobalAlias();
  
  preprocessLines(documents);

  processLines();

  qDebug() << "----------Assembly Result---------------\n";

  Assembled* assembled = new Assembled();
  assembled->warningLog = _warningLog;
  //if we succeed to assemble, then remove error list
  if(_success){
    qDebug() << "Success: true\n";
    assembled->isAssembled = true;
    assembled->assembly = new Assembly();
    assembled->assembly->instructions = _instructions; 
    assembled->assembly->addresses = _addresses;
  }
  //else we failed to assemble, then remvoe assembly part
  else{
    qDebug() << "Success: false\n";
    assembled->isAssembled = false;
    assembled->errorLog = _errorLog;
  }

  qDebug() << "Elasped time: " << timer.elapsed() << " msec\n";
  clear();
  return assembled;
}

void Assembler::preprocessLines(QStringList documents){
  qDebug() << "Preprocessing" << endl;

  int docNumber = 0;
  for(QString lines : documents){
    int lineNumber = 0;
    qDebug() << "Document: " << docNumber << endl;

    for(QString line  : lines.split("\n")){
      qDebug() << "Line: " << line << "\n";

      preprocessLine(docNumber, lineNumber, line);

      //increment line number by 1.
      lineNumber+=1;
      qDebug()<< "-\n";
    }

    docNumber += 1;
  }
}



void Assembler::preprocessLine(int docNumber, int lineNumber, QString line){
  //remove extra white space and comment
  line = line.trimmed().split(";").at(0).toUpper();
  qDebug() << "Trimmed: " << line << endl;

  //If empty then continue
  if(line.isEmpty()){ 
    qDebug() << "SKIP: line is empty\n-" << endl;
  }

  //tokenize element into string
  QStringList tokens = line.split(QRegExp("\\s+"));

  for (int i = 0; i < tokens.size(); i++)
    qDebug() << tokens.at(i) << endl;

  // Bail if there's nothing here.
  if(tokens.size() == 0){
    qDebug() << "Is it even possible to have zero for tokens size?\n";
    exit(-1);
  }


  //get next address 
  uint nextAddress;
  if(_preprocessedQueue->empty()){
    nextAddress = 0;
  }
  else{
    nextAddress = _preprocessedQueue->last().address + INSTRUCTION_SIZE;
  }

  //check whether the statement is label
  if(tokens.at(0).endsWith(":")){
    qDebug() << "Label detected" << endl;
    if(tokens.size() >= 1){
      throwError(docNumber, lineNumber, 1,"Invalid Format; Not a Label" );
      return;
    }

    //remove : at the end of the string
    QString label = tokens.at(0).left(tokens.at(0).length()-1); 

    //check the validity of label name
    QRegExp re("^[a-zA-Z][a-zA-Z0-9_]*$");  
    if (!re.exactMatch(label)){
      throwError(docNumber,lineNumber,0, "Invalid Format: " + label + " is not a Label");
      return;
    }

    //check whether label is already defined
    if(_labelTable->contains(label)){
      throwError(docNumber, lineNumber, 0, "Invalid Format: " + label + " is already defined");
      return;
    }

    qDebug() << "Symbol added: " << label << " = " << nextAddress << endl;
    _labelTable->insert(label, nextAddress);
    return;
  }
  else{
    
    //process through aliasTable
    for(int i = 0; i < tokens.size(); i++){
      QString str = tokens[i];
      if(_aliasTable->contains(str)){
        tokens[i] = _aliasTable->value(str);
        qDebug() <<"Alias resolved: " << str << " -> " << tokens[i] << endl;
      }
    }

    qDebug() << "Address added: " << nextAddress << "\n";

    //Preprcoessed data will be stored here
    Preprocessed preprocessed;
    preprocessed.docNumber = docNumber;
    preprocessed.lineNumber = lineNumber;
    preprocessed.address = nextAddress;
    preprocessed.tokens = tokens;
    _preprocessedQueue->append(preprocessed);
    return;
  }

}
void Assembler::processLines(){
  qDebug() << "Processing" <<endl;
 
  for(Preprocessed preprocessed : *_preprocessedQueue){
    //process each line
    processLine(preprocessed);

    qDebug()<< "-\n";
  } 
}


void Assembler::processLine(Preprocessed prep){
  qDebug() << "processing a line" << endl;
  int docNumber = prep.docNumber;
  int lineNumber = prep.lineNumber;
  uint address = prep.address;
  QStringList tokens = prep.tokens;

  
  // Grab the opcode and operands
  QString token1 = tokens.first();
  tokens.removeFirst();

  uint flag = CRS.nameTable["AL"];
  uint opcode = IRS.nameTable["NOP"];

  //IS token1 instruction?
  if(IRS.nameTable.contains(token1)){
    //Instruction deteceted!
    opcode = IRS.nameTable[token1];
    qDebug() << "Conversion: " << token1 << " -> " << opcode << endl;
  }
  else{
    //Token1 must be condition.
    if(CRS.nameTable.contains(token1)){
      flag = CRS.nameTable[token1];
      qDebug() << "Conversion: " << token1 << " -> " << flag << endl;

      QString token2 = tokens.first();
      tokens.removeFirst();

      //token 2 must be instruction
      if(IRS.nameTable.contains(token2)){
        //yes
        opcode = IRS.nameTable[token2];
        qDebug() << "Conversion: " << token1 << " -> " << flag << endl;
      }
      else{
        throwError(docNumber, lineNumber,1, "Invalid Symbol: " + token2);
      }
    }
    else{
      //okay, error
      throwError(docNumber,lineNumber,0,"Invalid Symbol: " +token1);
    }
  }
  uint operands[tokens.size()];




}

void Assembler::throwError(int docNumber, int lineNumber, int wordNumber, QString cause){
  Error error(docNumber, lineNumber, wordNumber, cause);
  _errorLog->append(error);
  _success=false;
  qDebug() << "Document Number: " << error.docNumber << endl;
  qDebug() << "Line Number: " << error.lineNumber << " \tWord Number: " << error.wordNumber << endl;
  qDebug() << "cause:\n" << error.cause <<endl;
}

void Assembler::throwWarning(int docNumber, int lineNumber, int wordNumber, QString cause){
  Warning warning(docNumber, lineNumber,wordNumber,cause);
  _warningLog->append(warning);
  qDebug() << "Document Number: " << warning.docNumber << endl;
  qDebug() << "Line Number: " << warning.lineNumber << " \tWord Number: " << warning.wordNumber << endl;
  qDebug() << "cause:\n" << warning.cause <<endl;
}
