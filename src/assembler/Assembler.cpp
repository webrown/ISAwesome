#include "Assembler.h" 

Assembler::Assembler(){
    //Do nothing
}

Assembler::~Assembler(){
    clear();
}

void Assembler::init(){
    qDebug() << "Initiating Assembler variables" ;
    _success = true;
    uint mainAddress = 0;

    _labelTable = new QMap<QString, uint>();
    _aliasTable = new QMap<QString, QString>();
    _macroTable = new QMap<QString, QStringList>();

    _errorLog = new QList<Error>();
    _warningLog = new QList<Warning>();

    _preprocessedQueue = new QList<Preprocessed>();
    _instructions = new QVector<uint>();
}

void Assembler::clear(){
    qDebug() << "Clear";

    if(_labelTable != NULL){
        delete _labelTable;
        _labelTable = NULL;
    }

    if(_aliasTable != NULL){
        delete _aliasTable;
        _aliasTable = NULL;
    }
    
    if(_macroTable != NULL){
        delete _macroTable;
        _macroTable = NULL;
    }

    if(_preprocessedQueue != NULL){
        delete _preprocessedQueue;
        _preprocessedQueue = NULL;
    }

    _errorLog = NULL;
    _instructions = NULL;
    _warningLog = NULL;
    qDebug() << "Assembler is cleared";
}

void Assembler::assemble(QString fileName, AssemblerConfiguration config){
    //Start time to measure how long it took to compile
    QTime timer;
    timer.start();

    qDebug() << "----------Start Assembly---------------" ;

    //initialize assembler
    _config = config;
    init();

    qDebug() << "----------Set Environment--------------";
    if(_config.useDefaultMacro == true){
        processFile("DefaultMacro");
    }
    if(_config.useGlobalMacro == true){
        processFile("GlobalMacro");
    }
    if(_config.useDefaultAlias == true){
        processFile("DefaultAlias");
    }
    if(_config.useGlobalAlias == true){
        processFile("GlobalAlias");
    }

    qDebug() << "----------Preprocess-------------------";

    processFile(fileName);

    qDebug() << "----------Process----------------------";

    processLines();

    qDebug() << "----------Assembly Result---------------" ;

    Assembled* assembled = new Assembled();
    assembled->warningLog = _warningLog;
    //if we succeed to assemble, then remove error list
    if(_success){
        qDebug() << "Success: true";
        assembled->isAssembled = true;
        assembled->instructions = _instructions; 
        delete assembled->errorLog;
    }
    //else we failed to assemble, then remvoe assembly part
    else{
        qDebug() << "Success: false";
        assembled->isAssembled = false;
        assembled->errorLog = _errorLog;
        delete assembled->instructions;
    }
    assembled->elaspedTime = timer.elapsed();

    qDebug() << "Elasped time: " << assembled->elaspedTime << " msec";
    clear();

    emit resultReady(assembled);
    return;
}

void Assembler::processFile(QString fileName){
    qDebug() << "Reading: " << fileName ;
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << fileName << " is not found" ;
        exit(-1);
    }

    QStringList document;
    while (!file.atEnd()) {
        document << file.readLine();
    }
    preprocessDocument(document, fileName);
}

void Assembler::preprocessDocument(QStringList document, QString fileName){
    int lineNumber = 0;

    //There are "correct" way of dealing local macro in file.
    //But who cares?
    bool isProcessingMacro = false;
    QStringList macroBuffer;

    for(QString line : document){
        qDebug() << "Line: " << line;

        //remove extra white space and comment
        line = line.trimmed().split(";").at(0).toUpper();
        qDebug() << "Simplified: " << line ;

        if(line == "#ENDMACRO"){
            qDebug() << "End special local macro subroutine" ;
            isProcessingMacro = false;

            //process through macro
            if(macroBuffer.isEmpty()){
                throwError(fileName, lineNumber, 0,"Invalid Format: macro definition can't be empty");
                continue;
            }
            QStringList tokens = macroBuffer.first().split(QRegExp("\\s+"));
            QRegExp re("^[a-zA-Z_][a-zA-Z0-9_]*");
            if(!re.exactMatch(tokens[0])){
                throwError(fileName, lineNumber - macroBuffer.size(), 0, "Invalid Formant: Not valid symbol");
                continue;
            }
            qDebug() << "New Macro defined" << tokens[0] ;
            _macroTable->insert(tokens[0], macroBuffer);
            macroBuffer = QStringList();
            continue;
        }
        //Special subroutine for checking macro
        if(isProcessingMacro){
            macroBuffer << line;
            continue;
        }
        if(line == "#DEFINEMACRO"){
            qDebug() << "Enter special local macro subroutine :)" ;
            isProcessingMacro = true;
            continue;
        }

        //Preprocess line
        preprocessLine(fileName, lineNumber, line);

        //increment line number by 1.
        lineNumber+=1;
        qDebug()<< "---";
    }

    if(isProcessingMacro == true){
        throwError(fileName, lineNumber, 0, "Invalid Format: Macro definition is not fully defined");
    }

}



void Assembler::preprocessLine(QString fileName, int lineNumber, QString line){
    //If empty then continue
    if(line.isEmpty()){ 
        qDebug() << "SKIP: line is empty" ;
        return;
    }

    //Check import;
    if(line.startsWith("#IMPORT")){
        QDir dir(fileName); 
        QString path = dir.filePath(line.remove(0,8));
        QFile file(path);
        if(file.exists() == false){
            throwError(fileName, lineNumber, 1, "Import failed: file doesn't exist");
            return;
        }
        this->processFile(path);
    }

    //Process alias
    if(line.startsWith("#ALIAS")){
        qDebug() << "Defining alias" ;
        line.remove(0,7);
        QStringList tokens = line.split(QRegExp("\\s+"));
        if(tokens.size() != 2){
            throwError(fileName, lineNumber, tokens.size(), "Invalid Format: Invalid argument");
            return;
        }
        QRegExp re("^[a-zA-Z_][a-zA-Z0-9_]*");
        if(!re.exactMatch(tokens[0])){
            throwError(fileName, lineNumber, 0, "Invalid Formant: Not valid symbol");
            return;
        }
        if(!re.exactMatch(tokens[1])){
            throwError(fileName, lineNumber, 1, "Invalid Formant: Not valid symbol");
            return;
        }
        qDebug() << tokens[0] << " = " << tokens[1];
        _aliasTable->insert(tokens[0], tokens[1]);
        return;
    }

    if(line.startsWith("#UNALIAS")){
        qDebug() << "Removing local alias" ;
        line.remove("#UNALIAS");
        QStringList tokens = line.split(QRegExp("\\s+"));
        if(tokens.size() != 1){
            throwError(fileName ,lineNumber, tokens.size(), "InvalidFormat: Wrong number of argument for unalias");
            return;
        }
        if(!_aliasTable->contains(tokens[0])){
            throwError(fileName ,lineNumber, 0, "InvalidFormat: undefined alias");
            return;
        }
        qDebug() << "alias " << tokens[0] << " is removed." ;
        _aliasTable-> remove(tokens[0]);
        return;
    }

    //tokenize element into string
    QStringList tokens = line.split(QRegExp("\\s+"));

    for (int i = 0; i < tokens.size(); i++)
        qDebug() << tokens.at(i) ;

    // Bail if there's nothing here.
    if(tokens.size() == 0){
        qDebug() << "Is it even possible to have zero for tokens size?";
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
        qDebug() << "Label detected" ;
        if(tokens.size() >= 1){
            throwError(fileName, lineNumber, 1,"Invalid Format; Not a Label" );
            return;
        }

        //remove : at the end of the string
        QString label = tokens.at(0).left(tokens.at(0).length()-1); 

        //check the validity of label name
        QRegExp re("^[a-zA-Z][a-zA-Z0-9_]*$");  
        if (!re.exactMatch(label)){
            throwError(fileName,lineNumber,0, "Invalid Format: " + label + " is not a Label");
            return;
        }

        //check whether label is already defined
        if(_labelTable->contains(label)){
            throwError(fileName, lineNumber, 0, "Invalid Format: " + label + " is already defined");
            return;
        }

        qDebug() << "Symbol added: " << label << " = " << nextAddress ;
        _labelTable->insert(label, nextAddress);
        return;
    }
    else{

        //process through aliasTable
        //And convert immediate to decimal
        for(int i = 0; i < tokens.size(); i++){
            QString str = tokens[i];
            if(_aliasTable->contains(str)){
                tokens[i] = _aliasTable->value(str);
                qDebug() <<"Alias resolved: " << str << " -> " << tokens[i] ;
            }
            if(str.startsWith("#0X")){
                str.remove(0,2);
                bool success;
                tokens[i] = str.toInt(&success, 16);
                if(success == false){
                    throwError(fileName, lineNumber, i, "Invalid Format: Not Hexadecimal");
                    return;
                }
            }
            if(str.startsWith("#0B")){
                str.remove(0,2);
                bool success;
                tokens[i] = str.toInt(&success, 2);
                if(success == false){
                    throwError(fileName ,lineNumber, i, "Invalid Format: Not Binary");
                    return;
                }
            }
        }

        qDebug() << "Address added: " << nextAddress;

        //Preprcoessed data will be stored here
        Preprocessed preprocessed;
        preprocessed.fileName = fileName;
        preprocessed.lineNumber = lineNumber;
        preprocessed.address = nextAddress;
        preprocessed.tokens = tokens;
        _preprocessedQueue->append(preprocessed);
        return;
    }
}

void Assembler::processLines(){
    for(Preprocessed preprocessed : *_preprocessedQueue){
        //process each line
        processLine(preprocessed);

        qDebug()<< "-";
    } 
}


void Assembler::processLine(Preprocessed prep){
    qDebug() << "processing a line" ;
    QString fileName = prep.fileName;
    int lineNumber = prep.lineNumber;
    uint address = prep.address;
    QStringList tokens = prep.tokens;


    // Grab the opcode and operands
    QString token1 = tokens.takeFirst();

    uint flag = CRS.nameTable["AL"];
    uint opcode = 000011; //=NOP
    InstructionDefinition* def;
    int operandTokenNumber = 0;


    //IS token1 instruction?
    if(IRS.nameTable.contains(token1)){
        //Instruction deteceted!
        def = IRS.nameTable[token1];
        qDebug() << "Conversion: " << token1 << " -> " << def->opcode ;
        operandTokenNumber = 1;
    }
    else{
        //Token1 must be condition.
        if(!CRS.nameTable.contains(token1)){
            //okay, error
            throwError(fileName,lineNumber,0,"Invalid Symbol: " +token1);
            return;
        }

        flag = CRS.nameTable[token1];
        qDebug() << "Conversion: " << token1 << " -> " << flag ;

        QString token2 = tokens.takeFirst();
        //token 2 must be instruction
        if(!IRS.nameTable.contains(token2)){
            throwError(fileName, lineNumber,1, "Invalid Symbol: " + token2);
            return;
        }    
        //yes
        def = IRS.nameTable[token2];
        qDebug() << "Conversion: " << token1 << " -> " << def->opcode ;
        operandTokenNumber =2;
    }
    opcode = def->opcode;

    ParseResult result = def->parse(tokens);
    if(result.error != "None"){
        throwError(fileName,lineNumber, result.failureLocation, result.error);
        return;
    }
    else if (result.warning != "None"){
        throwWarning(fileName, lineNumber, result.failureLocation, result.warning);
    }
    qDebug() << "Argument parsed: " << QString::number(result.parsed, 2).rightJustified(22,'0') ;

    //Generate instruction
    uint instruction = (((flag << 6) | opcode) << 22) | result.parsed;

    qDebug() << "Instruction generated: " << QString::number(instruction, 2).rightJustified(32,'0') ;
    _instructions->append(instruction);
    qDebug() << "---";
}


void Assembler::throwError(QString fileName, int lineNumber, int wordNumber, QString cause){
    Error error(cause, fileName, lineNumber, wordNumber);
    _errorLog->append(error);
    _success=false;
}

void Assembler::throwWarning(QString fileName, int lineNumber, int wordNumber, QString cause){
    Warning warning(cause, fileName, lineNumber,wordNumber);
    _warningLog->append(warning);
}
