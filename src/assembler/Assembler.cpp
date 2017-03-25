#include "Assembler.h" 

Assembler::Assembler(){
    qDebug() << "ASM: creating assembler";
    qRegisterMetaType<AssemblerConfiguration>();
    qRegisterMetaType<Assembled>();
}

Assembler::~Assembler(){
    qDebug() << "ASM: removing assembler";
    clear();
}

void Assembler::init(){
    qDebug() << "ASM: Initiating assembler" ;
    _success = true;
    mainAddress = HEADER_BUFFER;

    _labelTable = new QMap<QString, QString>();
    _aliasTable = new QMap<QString, QString>();
    _macroTable = new QMap<QString, QStringList>();

    _problemLog = new QList<Problem>();

    _preprocessedQueue = new QList<Preprocessed>();
    _instructions = new QVector<uint>();
}

void Assembler::clear(){
    qDebug() << "ASM: Clearing assembler";

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

    _problemLog = NULL;
    _instructions = NULL;
    qDebug() << "ASM: Assembler is cleared";
}

void Assembler::assemble(QString fileName, AssemblerConfiguration config, bool runAfter){
    qDebug() << "ASM: start assembly";
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

    //Consider wall option
    _success = (config.useWall == false)| (_problemLog->isEmpty() == true);
    Assembled* assembled = new Assembled();
    assembled->fileName = fileName;
    assembled->problemLog = _problemLog;
    //if we succeed to assemble, then remove error list
    if(_success){
        qDebug() << "Success: true";
        assembled->isAssembled = true;
        assembled->instructions = _instructions; 
    }
    //else we failed to assemble, then remvoe assembly part
    else{
        qDebug() << "Success: false";
        assembled->isAssembled = false;
    }
    assembled->elaspedTime = timer.elapsed();

    qDebug() << "Elasped time: " << assembled->elaspedTime << " msec";
    clear();

    emit resultReady(assembled, runAfter );
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
        line = line.split(";").at(0).trimmed().toUpper();
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

            QString header = tokens.takeFirst();
            QRegExp re("^[a-zA-Z_][a-zA-Z0-9_]*");
            if(!re.exactMatch(header)){
                throwError(fileName, lineNumber - macroBuffer.size(), 0, "Invalid Formant: Not valid symbol");
                continue;
            }
            QString arguments;
            for(QString token : tokens){
                arguments += token+ " ";
            }
            macroBuffer.replace(0, arguments.simplified());
            _macroTable->insert(header, macroBuffer);
            qDebug() << "New Macro defined" << header  << macroBuffer;
            macroBuffer = QStringList();
            lineNumber+=1;
            continue;
        }
        //Special subroutine for checking macro
        if(isProcessingMacro){
            macroBuffer << line;
            lineNumber+=1;
            continue;
        }
        if(line == "#DEFINEMACRO"){
            qDebug() << "Enter special local macro subroutine :)" ;
            isProcessingMacro = true;
            lineNumber +=1;
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

    //Check Merge;
    if(line.startsWith("#MERGE")){
        QFileInfo info(fileName); 
        QString path = info.dir().absolutePath() + "/"+  line.remove(0,6).toLower().simplified();
        qDebug() << "Merge this file: " << path;
        QFile file(path);
        if(file.exists() == false){
            throwError(fileName, lineNumber, 0, "Merge failed: file doesn't exist");
            return;
        }
        this->processFile(path);
        return;
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
        QStringList tokens = line.simplified().split(QRegExp("\\s+"));
        if(tokens.size() != 1){
            throwError(fileName ,lineNumber, tokens.size(), "InvalidFormat: Wrong number of argument for unalias");
            return;
        }
        if(!_aliasTable->contains(tokens[0])){
            throwError(fileName ,lineNumber, 1, "InvalidFormat: undefined alias");
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
        nextAddress = _config.useMainEntry ? HEADER_BUFFER : 0;
    }
    else{
        nextAddress = _preprocessedQueue->last().address + INSTRUCTION_SIZE;
    }

    //Check import
    if(line.startsWith("#IMPORT")){
        QFileInfo info(fileName); 
        QString path = info.dir().absolutePath() + "/"+  line.remove(0,7).simplified();
        qDebug() << "Import this file: " << path << "later";
        QFile file(path);
        if(file.exists() == false){
            throwError(fileName, lineNumber, 1, "Import failed: file doesn't exist");
            return;
        }

        qDebug() << "NOT implemented";

        //Preprcoessed data will be stored here
/*         Preprocessed preprocessed; */
        // preprocessed.fileName = path;
        // preprocessed.lineNumber = -1;
        // preprocessed.address = nextAddress;
        // preprocessed.tokens = tokens;
/*         _ preprocessedQueue->append(preprocessed);*/
        return;
    }

    //check whether the statement is label
    if(tokens.at(0).endsWith(":")){
        qDebug() << "Label detected" ;
        if(tokens.size() > 1){
            throwError(fileName, lineNumber, tokens.size(),"Invalid Format: Not a Label" );
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
        _labelTable->insert(label, QString::number(nextAddress));
        //Collect main Address
        if(_config.useMainEntry && label == "MAIN"){
            mainAddress = nextAddress;
        }
        return;
    }
    else{
        //find out instruction location
        int instructionLoc =0;
        if(CRS.nameTable.contains(tokens[0])){
            instructionLoc = 1;
        }
        if(_macroTable->contains(tokens[instructionLoc])){
            qDebug() << "Macro detected!";
            QStringList macroDef = _macroTable->value(tokens[instructionLoc]);
            QStringList args = macroDef.first().split(QRegExp("\\s+"));

            int requiredNumberOfArgument = args.size();
            int numberOfArgument = tokens.size() - instructionLoc -1;
            // qDebug() << args;
            // qDebug() << QString::number(requiredNumberOfArgument) << QString::number(numberOfArgument);
            if(numberOfArgument != requiredNumberOfArgument){
                throwError(fileName, lineNumber, instructionLoc + numberOfArgument, "Invalid Number of arguments for macro");
                return;
            }
            qDebug() << "Build replace Map";
            //build replaceMap
            QMap<QString, QString> _replaceMap;
            for(int i = 0; i < requiredNumberOfArgument; i++){
                _replaceMap[args[i]] = tokens[i + instructionLoc + 1];
            }
            qDebug() << _replaceMap;
            qDebug() << "Replace begins";
            for(int i =1; i < macroDef.size(); i++){
                QString line = macroDef[i];
                for(QString key : _replaceMap.keys()){
                    line.replace(key, _replaceMap[key]);
                }
                QStringList tokens = line.split(QRegExp("\\s+"));

                //-------------------------Yeah, I m gonna fix this

                //process through aliasTable
                //And convert immediate to decimal
                for(int i = 0; i < tokens.size(); i++){
                    QString str = tokens[i];
                    if(_aliasTable->contains(str)){
                        tokens[i] = _aliasTable->value(str);
                        qDebug() <<"Alias resolved: " << str << " -> " << tokens[i] ;
                    }

                    if(str.startsWith("#0X")){
                        str.remove(0,3);
                        bool success;
                        tokens[i] = QString::number(str.toInt(&success, 16));
                        qDebug() << "HEX to DEC: " << str ;
                        if(success == false){
                            throwError(fileName, lineNumber, i, "Invalid Format:  Not Hexadecimal");
                            return;
                        }
                    }
                    if(str.startsWith("#0B")){
                        str.remove(0,3);
                        bool success;
                        tokens[i] = QString::number(str.toInt(&success, 2));
                        qDebug() << "BIN to DEC: " << str;
                        if(success == false){
                            throwError(fileName ,lineNumber, i, "Invalid Format: Not Binary");
                            return;
                        }
                    }
                }
                //-----------------------But not now

                //Preprcoessed data will be stored here
                Preprocessed preprocessed;
                preprocessed.fileName = fileName;
                preprocessed.lineNumber = lineNumber;
                preprocessed.address = nextAddress;
                preprocessed.tokens = tokens;
                _preprocessedQueue->append(preprocessed);
                nextAddress += INSTRUCTION_SIZE;
            }
            return;
        }

        //process through aliasTable
        //And convert immediate to decimal
        for(int i = 0; i < tokens.size(); i++){
            QString str = tokens[i];
            if(_aliasTable->contains(str)){
                tokens[i] = _aliasTable->value(str);
                qDebug() <<"Alias resolved: " << str << " -> " << tokens[i] ;
            }

            if(str.startsWith("#0X")){
                str.remove(0,3);
                bool success;
                tokens[i] = QString::number(str.toInt(&success, 16));
                qDebug() << "HEX to DEC: " << str ;
                if(success == false){
                    throwError(fileName, lineNumber, i, "Invalid Format:  Not Hexadecimal");
                    return;
                }
            }
            if(str.startsWith("#0B")){
                str.remove(0,3);
                bool success;
                tokens[i] = QString::number(str.toInt(&success, 2));
                qDebug() << "BIN to DEC: " << str;
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
    if(_config.useMainEntry){
        writeHeader();
    }
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

    uint flag = CRS.nameTable["AL"];
    uint opcode = IRS.nameTable["NOP"]->opcode; //=NOP
    InstructionDefinition* def;
    int operandTokenNumber = 0;


    // Grab the opcode and operands
    QString token1 = tokens.takeFirst();

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
    qDebug() << "Argument: " << tokens ;

    for(int i =0; i < tokens.size(); i++){
        QString str = tokens[i];
        if(_labelTable->contains(str)){
            tokens[i] = _labelTable->value(str);
            qDebug() <<"Label resolved: " << str << " -> " << tokens[i] ;
        }
    }

    ParseResult result = def->parse(tokens);
    if(result.error != "None"){
        throwError(fileName,lineNumber, operandTokenNumber + result.failureLocation, result.error);
        return;
    }
    else if (result.warning != "None"){
        throwWarning(fileName, lineNumber, operandTokenNumber + result.failureLocation, result.warning);
    }
    qDebug() << "Argument parsed: " << QString::number(result.parsed, 2).rightJustified(22,'0') ;

    //Generate instruction
    uint instruction = (((flag << 6) | opcode) << 22) | result.parsed;

    qDebug() << "Instruction generated: " << QString::number(instruction, 2).rightJustified(32,'0') ;
    _instructions->append(instruction);
    qDebug() << "---";
}


void Assembler::throwError(QString fileName, int lineNumber, int wordNumber, QString cause){
    Problem problem(ERROR, cause, fileName, lineNumber, wordNumber);
    _problemLog->append(problem);
    _success=false;
}

void Assembler::throwWarning(QString fileName, int lineNumber, int wordNumber, QString cause){
    Problem warning(WARNING, cause, fileName, lineNumber,wordNumber);
    _problemLog->append(warning);
}

void Assembler::writeHeader(){
    uint lastAddress;
    if(_preprocessedQueue->empty()){
        lastAddress = _config.useMainEntry ? HEADER_BUFFER : 0u;
    }
    else{
        lastAddress = _preprocessedQueue->last().address + INSTRUCTION_SIZE;
    }

    uint a = lastAddress & ~((1u<<16u)-1u);
    uint b = lastAddress & ((1u<<16u)-1u);
    uint c = mainAddress & ~((1u<<16u)-1u);
    uint d = mainAddress & ((1u<<16u)-1u);
    QStringList header;
    header 
        << ("CPY " + QString::number(a) + " R21")
        << ("LSL 16 R21")
        << ("ADD " + QString::number(b) + " R21")
        << ("CPY R21 R22")
        << ("CPY " + QString::number(c) + " R20")
        << ("LSL 16 R21")
        << ("ADD " + QString::number(d) + " R20")
        << ("BL R20");

    int i =0;
    for(QString line : header){
        Preprocessed preprocessed;
        preprocessed.fileName = "System";
        preprocessed.lineNumber = i;
        preprocessed.address = i * INSTRUCTION_SIZE;
        preprocessed.tokens = line.split(QRegExp("\\s+"));
        qDebug() << preprocessed.tokens;
        _preprocessedQueue->insert(i++,preprocessed);
    }
}

void Assembler::immiMacro(QString front, uint immi, QString end, uint nextAddress){
    uint a = immi & ~((1<<16)-1);
    uint b = immi & ((1<<16)-1);
    QStringList macro;
    macro 
        << ("STO R0 R21")
        << ("ADD 4 R21")
        << ("CPY " + QString::number(a) + " R0")
        << ("LSL 16 R0")
        << ("ADD " + QString::number(b) + " R0")
        << (front + " R0 " + end)
        << ("SUB 4 R21")
        << ("LOD R21 R0") 
        ;
    int i =0;
    for(QString line : macro){
        Preprocessed preprocessed;
        preprocessed.fileName = "System";
        preprocessed.lineNumber = i;
        preprocessed.address = i * INSTRUCTION_SIZE;
        preprocessed.tokens = line.split(QRegExp("\\s+"));
        qDebug() << preprocessed.tokens;
        _preprocessedQueue->insert(i++,preprocessed);
    }
}
