
#include "Assembler.h" 

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
    qDebug() << "Initiating Assembler variables" << endl;
    _success = true;
    uint mainAddress = 0;

    _labelTable = new QMap<QString, uint>();
    _aliasTable = new QMap<QString, QString>();
    _macroTable = new QMap<QString, QStringList>();

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
    if(_macroTable != NULL){
        delete _macroTable;
    }
    if(_preprocessedQueue != NULL){
        delete _preprocessedQueue;
    }

    //TODO : delete errorlog and instructions based on the result
    _errorLog = NULL;
    _instructions = NULL;
    _addresses = NULL;
    _warningLog = NULL;
}

Assembled* Assembler::assemble(QStringList documents, AssemblerConfiguration config){
    //Start time to measure how long it took to compile
    QTime timer;
    timer.start();

    qDebug() << "----------Start Assembly-------------" << endl;

    //initialize assembler
    _config = config;
    init();

    preprocessLines(documents);

    processLines();

    qDebug() << "----------Assembly Result---------------\n";

    Assembled* assembled = new Assembled();
    assembled->warningLog = _warningLog;
    //if we succeed to assemble, then remove error list
    if(_success){
        qDebug() << "Success: true\n";
        assembled->isAssembled = true;
        assembled->instructions = _instructions; 
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

void Assembler::loadFromSystemFile(QString fileName){
    qDebug() << "Processing " << fileName << endl;
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << fileName << " is not found" << endl;
        exit(-1);
    }

    int lineNumber = 1;
    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        preprocessLine(-1, lineNumber++, line);
    }
}

void Assembler::preprocessLines(QStringList documents){
    qDebug() << "Preprocessing" << endl;

    if(_config.useDefaultMacro == true){
        loadFromSystemFile("DefaultMacro");
    }
    if(_config.useGlobalMacro == true){
        loadFromSystemFile("GlobalMacro");
    }
    if(_config.useDefaultAlias == true){
        loadFromSystemFile("DefaultAlias");
    }
    if(_config.useGlobalAlias == true){
        loadFromSystemFile("GlobalAlias");
    }
    if(_config.useOrder == true){
        sortDocuments(documents);
    }

    int docNumber = 0;
    for(QString lines : documents){
        int lineNumber = 0;
        qDebug() << "Processing Document: " << docNumber << endl;

        //There are "correct" way of dealing local macro in file.
        //But who cares?
        bool isProcessingMacro = false;
        QStringList macroBuffer;

        for(QString line  : lines.split("\n")){
            qDebug() << "Line: " << line << "\n";
            
            //remove extra white space and comment
            line = line.trimmed().split(";").at(0).toUpper();
            qDebug() << "Trimmed: " << line << endl;

            //Special subroutine for checking macro
            if(isProcessingMacro){
                macroBuffer << line;
            }
            if(line == "#DEFINEMACRO"){
                qDebug() << "Enter special local macro subroutine :)" << endl;
                isProcessingMacro = true;
            }
            if(line == "#ENDMACRO"){
                qDebug() << "End special local macro subroutine" << endl;
                isProcessingMacro = false;

                //process through macro
                if(macroBuffer.isEmpty()){
                    throwError(docNumber, lineNumber, 0,"Invalid Format: macro definition can't be empty");
                    continue;
                }
                QStringList tokens = macroBuffer.first().split(QRegExp("\\s+"));
                QRegExp re("^[a-zA-Z_][a-zA-Z0-9_]*");
                if(!re.exactMatch(tokens[0])){
                    throwError(docNumber, lineNumber - macroBuffer.size(), 0, "Invalid Formant: Not valid symbol");
                    continue;
                }
                qDebug() << "New Macro defined" << tokens[0] << endl;
                _macroTable->insert(tokens[0], macroBuffer);
                macroBuffer = QStringList();
            }

            preprocessLine(docNumber, lineNumber, line);

            //increment line number by 1.
            lineNumber+=1;
            qDebug()<< "-\n";
        }

        if(isProcessingMacro == true){
            throwError(docNumber, lineNumber, 0, "Invalid Format: Macro definition is not fully defined");
        }

        docNumber += 1;
    }
}

void Assembler::sortDocuments(QStringList documents){
    qDebug() << "Sorting documents" << endl;
    QMultiMap<int, QString> map;

    int n = 0;
    for(QString document : documents){
        QString firstLine = document.section("\n", 0,0).simplified().toUpper();
        if(firstLine.startsWith("#ORDER")){
            int order = firstLine.remove("#ORDER").toInt();
            qDebug() << (n+1)<<"th document is assigned to " << order << endl;
            map.insert(order, document);
        }
        else{
            qDebug() << (n+1)<<"th document is assigned to " << INT_MAX << endl;
            map.insert(INT_MAX, document);
        }
    }
    //I am pretty sure there is more efficient algorith mfor this problem, but who cares?
    n = 0;
    for(int order : map.keys()){
        for(QString document : map.values(order)){
            documents.replace(n++,document);
        }
    }
}



void Assembler::preprocessLine(int docNumber, int lineNumber, QString line){
    //If empty then continue
    if(line.isEmpty()){ 
        qDebug() << "SKIP: line is empty\n-" << endl;
        return;
    }

    //Process alias
    if(line.startsWith("#ALIAS")){
        qDebug() << "Defining local alias" << endl;
        line.remove("#ALIAS");
        QStringList tokens = line.split(QRegExp("\\s+"));
        if(tokens.size() != 2){
            throwError(docNumber, lineNumber, tokens.size(), "Invalid Format: Invalid argument");
            return;
        }
        QRegExp re("^[a-zA-Z_][a-zA-Z0-9_]*");
        if(!re.exactMatch(tokens[0])){
            throwError(docNumber, lineNumber, 0, "Invalid Formant: Not valid symbol");
            return;
        }
        if(!re.exactMatch(tokens[1])){
            throwError(docNumber, lineNumber, 1, "Invalid Formant: Not valid symbol");
            return;
        }
        qDebug() << tokens[0] << " = " << tokens[1];
        _aliasTable->insert(tokens[0], tokens[1]);
        return;
    }

    if(line.startsWith("#UNALIAS")){
        qDebug() << "Removing local alias" << endl;
        line.remove("#UNALIAS");
        QStringList tokens = line.split(QRegExp("\\s+"));
        if(tokens.size() != 1){
            throwError(docNumber ,lineNumber, tokens.size(), "InvalidFormat: Wrong number of argument for unalias");
            return;
        }
        if(!_aliasTable->contains(tokens[0])){
            throwError(docNumber ,lineNumber, 0, "InvalidFormat: undefined alias");
            return;
        }
        qDebug() << "alias " << tokens[0] << " is removed." << endl;
        _aliasTable-> remove(tokens[0]);
        return;
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
            if(str.startsWith("#0X")){
                str.remove("#0X");
                bool success;
                tokens[i] = str.toInt(&success, 16);
                if(success == false){
                    throwError(docNumber, lineNumber, i, "Invalid Format: Not Hexadecimal");
                    return;
                }
            }
            if(str.startsWith("#0B")){
                str.remove("#0B");
                bool success;
                tokens[i] = str.toInt(&success, 2);
                if(success == false){
                    throwError(docNumber ,lineNumber, i, "Invalid Format: Not Binary");
                    return;
                }
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
    QString token1 = tokens.takeFirst();

    uint flag = CRS.nameTable["AL"];
    uint opcode = IRS.nameTable["NOP"];
    int operandTokenNumber = 0;
    

    //IS token1 instruction?
    if(IRS.nameTable.contains(token1)){
        //Instruction deteceted!
        opcode = IRS.nameTable[token1];
        qDebug() << "Conversion: " << token1 << " -> " << opcode << endl;
        operandTokenNumber = 1;
    }
    else{
        //Token1 must be condition.
        if(!CRS.nameTable.contains(token1)){
            //okay, error
            throwError(docNumber,lineNumber,0,"Invalid Symbol: " +token1);
            return;
        }

        flag = CRS.nameTable[token1];
        qDebug() << "Conversion: " << token1 << " -> " << flag << endl;

        QString token2 = tokens.takeFirst();
        //token 2 must be instruction
        if(!IRS.nameTable.contains(token2)){
            throwError(docNumber, lineNumber,1, "Invalid Symbol: " + token2);
            return;
        }    
        //yes
        opcode = IRS.nameTable[token2];
        qDebug() << "Conversion: " << token1 << " -> " << flag << endl;
        operandTokenNumber =2;
    }

    uint args;
    int availableArgTypes = IRS.argTable[opcode];


    
    //If instruction is branch with immediate
    if(opcode == 0){
           if(tokens.size() > 1 || tokens.size() != 0){
               throwError(docNumber, lineNumber, operandTokenNumber + tokens.size()-1, "Branch instruction only require 1 operands");
               return;
           }
           bool okay;
           args = tokens[0].toInt(&okay, 10);
           if(okay == false && args >= (1<<23)){
               throwError(docNumber, lineNumber, operandTokenNumber, "Branch instruction requires immediate 22");
               return;
           }
    }
    else if(opcode ==1){
           if(tokens.size() > 1 || tokens.size() != 0){
               throwError(docNumber, lineNumber, operandTokenNumber + tokens.size()-1, "Branch instruction only require 1 operands");
               return;
           }
           if(intReg.exactMatch(tokens[0])){
               args = convertRegister(tokens[0]);
           }
           else if(floatReg.exactMatch(tokens[1])){
               throwWarning(docNumber,lineNumber, operandTokenNumber, "Branch prefers integer register");
               args = convertRegister(tokens[0]);
           }
           else{
               throwError(docNumber, lineNumber, operandTokenNumber, "Branch with Register requires register");
               return;
           }
    }

     
    //Generate instruction
    uint instruction = (((flag << 6) | opcode) << 22) | args;

    qDebug() << "Instruction generated: " << QString::number(instruction, 2).rightJustified(32,'0') << endl;
    _instructions->append(args);
}

uint convertRegister(QString str){
    str.remove("R");
    return str.toInt();
}

void Assembler::throwError(int docNumber, int lineNumber, int wordNumber, QString cause){
    Error error(docNumber, lineNumber, wordNumber, cause);
    _errorLog->append(error);
    _success=false;
}

void Assembler::throwWarning(int docNumber, int lineNumber, int wordNumber, QString cause){
    Warning warning(docNumber, lineNumber,wordNumber,cause);
    _warningLog->append(warning);
}
