#include "Assembler.h" 

Assembler::Assembler(){ qDebug() << "ASM: creating assembler";
    qRegisterMetaType<AssemblerConfiguration>();
    qRegisterMetaType<Assembled>();
}

Assembler::~Assembler(){
    qDebug() << "ASM: removing assembler";
    clear();
}

void Assembler::setUpLogging(QString fileName){
    qDebug() << "ASM: set up logging file";

    QFileInfo info(fileName);
    _logFile = new QFile(info.completeBaseName() + "_" + QTime::currentTime().toString("HH_mm_ss") + ".log");

    if(_logFile->open(QIODevice::WriteOnly | QIODevice::Text) == false){
        qDebug() << "Log can't be created";
        exit(-1);
    }
    _log = new QTextStream(_logFile);
}

void Assembler::init(){
    qDebug() << "ASM: Initiating assembler" ;
    _success = true;
    _hasWarning = false;
    _dataMode = false;
    _endAddress = _config.useMainEntry ? HEADER_BUFFER : 0;
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
    if(_log != NULL){
        delete _log;
        _log = NULL;
    }
    if(_logFile != NULL){
        delete _logFile;
        _logFile = NULL;
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

    //set up logging file
    setUpLogging(fileName);

    (*_log)<<("----------Start Assembly---------------\n") ;

    //Save config
    _config = config;

    //initialize assembler
    init();


    (*_log)<<("----------Set Environment--------------\n");
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

    (*_log) << "----------Preprocess-------------------\n";

    processFile(fileName);

    (*_log) << "----------Process----------------------\n";

    processLines();

    (*_log) << "----------Assembly Result--------------\n" ;

    //Consider wall option
    _success = ((config.useWall == false) | (_hasWarning == false)) & _success;
    Assembled* assembled = new Assembled();
    assembled->fileName = fileName;
    assembled->problemLog = _problemLog;
    //if we succeed to assemble, then remove error list
    if(_success){
        (*_log) << "Success: true" <<endl;
        assembled->isAssembled = true;
        assembled->program = new Program();
        assembled->program->instructions = _instructions; 
        assembled->program->instructionEndAddress = _endAddress;
        assembled->program->dataEndAddress = _instructions->size() * INSTRUCTION_SIZE;
        assembled->program->size = _instructions->size();

    }
    //else we failed to assemble, then remvoe assembly part
    else{
        (*_log) << "Success: false" << endl;
        assembled->isAssembled = false;
    }
    (*_log) << "Has Warning: " << _hasWarning <<endl;
    assembled->elaspedTime = timer.elapsed();

    (*_log) << "Elasped time: " << assembled->elaspedTime << " msec"<<endl;
    clear();

    qDebug() << "ASM: assembly complete";
    emit resultReady(assembled, runAfter );
    return;
}

void Assembler::processFile(QString fileName){
    (*_log) << "-------"<< endl;
    (*_log) << "Reading: " << fileName <<endl;
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "ASM: " <<fileName << " is not found" ;
        exit(-1);
    }

    QStringList document;
    while (!file.atEnd()) {
        document << file.readLine();
    }
    preprocessDocument(document, fileName);
    (*_log) << "-------"<< endl;
    return;
}

void Assembler::preprocessDocument(QStringList document, QString fileName){
    int lineNumber = 0;

    //There are "correct" way of dealing local macro in file.
    //But who cares?
    bool isProcessingMacro = false;
    QStringList macroBuffer;

    for(QString line : document){
        (*_log) << "Line: " << line;

        //remove extra white space and comment
        line = line.split(";").at(0).trimmed().toUpper();
        (*_log) << "Simplified: " << line <<endl;

        if(line == "#ENDMACRO"){
            (*_log) << "End special local macro subroutine" <<endl;
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
            (*_log) << "New Macro defined" << header << endl;
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
            (*_log) << "Enter special local macro subroutine :)" <<endl;
            isProcessingMacro = true;
            lineNumber +=1;
            continue;
        }

        //Preprocess line
        preprocessLine(fileName, lineNumber, line);

        //increment line number by 1.
        lineNumber+=1;
        (*_log) << "---" << endl;
    }

    if(isProcessingMacro == true){
        throwError(fileName, lineNumber, 0, "Invalid Format: Macro definition is not fully defined");
    }

}



void Assembler::preprocessLine(QString fileName, int lineNumber, QString line){
    //If empty then continue
    if(line.isEmpty()){ 
        (*_log) << "SKIP: line is empty" << endl;
        return;
    }


    //Check Merge;
    if(line.startsWith("#MERGE")){
        QFileInfo info(fileName); 
        QString path = info.dir().absolutePath() + "/"+  line.remove(0,6).toLower().simplified();
        (*_log) << "Merge this file: " << path << endl;
        QFile file(path);
        if(file.exists() == false){
            return;
        }
        this->processFile(path);
        return;
    }
    //Process alias
    if(line.startsWith("#ALIAS")){
        (*_log) << "Defining alias" <<endl;
        line.remove(0,7);
        QStringList tokens = line.split(QRegExp("\\s+"));
        if(tokens.size() != 2){
            throwError(fileName, lineNumber, tokens.size(), "Invalid Format: Invalid number of argument");
            return;
        }
        QRegExp re("^[a-zA-Z_][a-zA-Z0-9_]*");
        if(!re.exactMatch(tokens[0])){
            throwError(fileName, lineNumber, 0, "Invalid Formant: \"" + tokens[0]+ "\" Not valid symbol");
            return;
        }
        if(!re.exactMatch(tokens[1])){
            throwError(fileName, lineNumber, 1, "Invalid Formant: \"" + tokens[1]+"\" Not valid symbol");
            return;
        }
        (*_log) << tokens[0] << " = " << tokens[1] << endl;
        _aliasTable->insert(tokens[0], tokens[1]);
        return;
    }

    if(line.startsWith("#UNALIAS")){
        (*_log) << "Removing local alias" ;
        line.remove("#UNALIAS");
        QStringList tokens = line.simplified().split(QRegExp("\\s+"));
        if(tokens.size() != 1){
            throwError(fileName ,lineNumber, tokens.size(), "InvalidFormat: Wrong number of argument for unalias");
            return;
        }
        if(!_aliasTable->contains(tokens[0])){
            throwError(fileName ,lineNumber, 1, "InvalidFormat: \""+tokens[0] + "\" is undefined");
            return;
        }
        (*_log) << "alias " << tokens[0] << " is removed." << endl;
        _aliasTable-> remove(tokens[0]);
        return;
    }

    //tokenize element into string
    QStringList tokens = line.split(QRegExp("\\s+"));

    (*_log) << "TOKENS: ";
    for (int i = 0; i < tokens.size(); i++)
        (*_log) << tokens.at(i) ;
    (*_log) << endl;


    // Bail if there's nothing here.
    if(tokens.size() == 0){
        qDebug() << "ASM: Is it even possible to have zero for tokens size?";
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

    if(line.startsWith("#DATA")){
        (*_log) << "Data mode on" << endl;
        _dataMode = true;
        //previous should be the last one
        _endAddress = nextAddress;
        return;
    }
    


    //Check import
    if(line.startsWith("#IMPORT")){
        QFileInfo info(fileName); 
        QString path = info.dir().absolutePath() + "/"+  line.remove(0,7).simplified();
        (*_log) << "Import this file: " << path << "later" << endl;
        QFile file(path);
        if(file.exists() == false){
            throwError(fileName, lineNumber, 1, "Import failed: file doesn't exist");
            return;
        }

        qDebug() << "ASM: IMPORT is not implemented";

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
        (*_log) << "Label detected" << endl;
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

        (*_log) << "Symbol added: " << label << " = " << nextAddress ;
        _labelTable->insert(label, QString::number(nextAddress));
        //Collect main Address
        if(_config.useMainEntry && label == "MAIN"){
            mainAddress = nextAddress;
        }
        return;
    }
    else{
        if(_dataMode == true){

            QStringList dataList = line.split(QRegExp("\\s+"));
            for(QString str : dataList){
                QStringList tokens;
                tokens << "DATA";
                if(str.startsWith("#0X")){
                    str.remove(0,3);
                    bool success;
                    tokens[1] = QString::number(str.toInt(&success, 16));
                    (*_log) << "HEX to DEC: " << str  <<endl;
                    if(success == false){
                        throwError(fileName, lineNumber, 1, "Invalid Format:  Not Hexadecimal");
                        return;
                    }
                }
                if(str.startsWith("#0B")){
                    str.remove(0,3);
                    bool success;
                    tokens[1] = QString::number(str.toInt(&success, 2));
                    (*_log) << "BIN to DEC: " << str <<endl;
                    if(success == false){
                        throwError(fileName ,lineNumber, 1, "Invalid Format: Not Binary");
                        return;
                    }
                }
                tokens << str;
                (*_log) << "Data processed: " << str << endl;

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
        //find out instruction location
        int instructionLoc =0;
        if(CRS.nameTable.contains(tokens[0])){
            instructionLoc = 1;
        }
        if(_macroTable->contains(tokens[instructionLoc])){
            (*_log) << "Macro detected!";
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
            (*_log) << "Build replace Map";
            //build replaceMap
            QMap<QString, QString> _replaceMap;
            for(int i = 0; i < requiredNumberOfArgument; i++){
                _replaceMap[args[i]] = tokens[i + instructionLoc + 1];
            }

            //http://stackoverflow.com/questions/18645134/how-to-show-all-keys-inside-qmap-with-qstringlist
            QMap<QString, QString>::iterator it;
            for (it = _replaceMap.begin(); it != _replaceMap.end(); ++it) {
                // Format output here.
                (*_log) << QString("%1 : %2").arg(it.key()).arg(it.value()) << endl;
            }
            (*_log) << "Replace begins";
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
                        (*_log) <<"Alias resolved: " << str << " -> " << tokens[i] <<endl;
                    }

                    if(str.startsWith("#0X")){
                        str.remove(0,3);
                        bool success;
                        tokens[i] = QString::number(str.toInt(&success, 16));
                        (*_log) << "HEX to DEC: " << str  <<endl;
                        if(success == false){
                            throwError(fileName, lineNumber, i, "Invalid Format:  Not Hexadecimal");
                            return;
                        }
                    }
                    if(str.startsWith("#0B")){
                        str.remove(0,3);
                        bool success;
                        tokens[i] = QString::number(str.toInt(&success, 2));
                        (*_log) << "BIN to DEC: " << str <<endl;
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
                _endAddress = nextAddress;
            }
            return;
        }

        //process through aliasTable
        //And convert immediate to decimal
        for(int i = 0; i < tokens.size(); i++){
            QString str = tokens[i];
            if(_aliasTable->contains(str)){
                tokens[i] = _aliasTable->value(str);
                (*_log) <<"Alias resolved: " << str << " -> " << tokens[i] <<endl;
            }

            if(str.startsWith("#0X")){
                str.remove(0,3);
                bool success;
                tokens[i] = QString::number(str.toInt(&success, 16));
                (*_log) << "HEX to DEC: " << str <<endl;
                if(success == false){
                    throwError(fileName, lineNumber, i, "Invalid Format:  Not Hexadecimal");
                    return;
                }
            }
            if(str.startsWith("#0B")){
                str.remove(0,3);
                bool success;
                tokens[i] = QString::number(str.toInt(&success, 2));
                (*_log) << "BIN to DEC: " << str <<endl;
                if(success == false){
                    throwError(fileName ,lineNumber, i, "Invalid Format: Not Binary");
                    return;
                }
            }
        }

        (*_log) << "Address added: " << nextAddress <<endl;

        //Preprcoessed data will be stored here
        Preprocessed preprocessed;
        preprocessed.fileName = fileName;
        preprocessed.lineNumber = lineNumber;
        preprocessed.address = nextAddress;
        preprocessed.tokens = tokens;
        _preprocessedQueue->append(preprocessed);
        _endAddress = nextAddress;
        
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

        (*_log)<< "-"<< endl;
    } 
}


void Assembler::processLine(Preprocessed prep){
    (*_log) << "processing a line" <<endl;
    QString fileName = prep.fileName;
    int lineNumber = prep.lineNumber;
    // uint address = prep.address;
    QStringList tokens = prep.tokens;

    if(tokens[0] == "DATA"){
        (*_log) << "Processing data: " << tokens[1] <<endl;

        bool ok;
        uint data = tokens[1].toUInt(&ok);
        if(ok == false){
            throwError(fileName, lineNumber, 1, "INVALID FORMAT: "+tokens[1] + " is not a number");
            return;
        }
        _instructions->append(data);
        //TODO check ok and printo ut stuff for D in preprocess
        (*_log) << "Data inserted: " << tokens[1] <<endl;
        (*_log) << "---" <<endl;
        return;
    }

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
        (*_log) << "Conversion: " << token1 << " -> " << def->opcode <<endl;
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
        (*_log) << "Conversion: " << token1 << " -> " << flag <<endl;

        QString token2 = tokens.takeFirst();
        //token 2 must be instruction
        if(!IRS.nameTable.contains(token2)){
            throwError(fileName, lineNumber,1, "Invalid Symbol: " + token2);
            return;
        }    
        //yes
        def = IRS.nameTable[token2];
        (*_log) << "Conversion: " << token1 << " -> " << def->opcode <<endl;
        operandTokenNumber =2;
    }
    opcode = def->opcode;
    (*_log) << "Argument: ";
    for(QString token : tokens){
        (*_log)<< token;
    }
    (*_log) <<endl;

    for(int i =0; i < tokens.size(); i++){
        QString str = tokens[i];
        if(_labelTable->contains(str)){
            tokens[i] = _labelTable->value(str);
            (*_log) <<"Label resolved: " << str << " -> " << tokens[i] <<endl;
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
    (*_log) << "Argument parsed: " << QString::number(result.parsed, 2).rightJustified(22,'0') <<endl;

    //Generate instruction
    uint instruction = (((flag << 6) | opcode) << 22) | result.parsed;

    (*_log) << "Instruction generated: " << QString::number(instruction, 2).rightJustified(32,'0') <<endl;
    _instructions->append(instruction);
    (*_log) << "---" <<endl;
}


void Assembler::throwError(QString fileName, int lineNumber, int wordNumber, QString cause){
    (*_log) << "ERROR" <<endl; 
    (*_log) << "File Name: " << fileName <<endl;
    (*_log) << "Line Number: " << lineNumber << " \tWord Number: " << wordNumber <<endl;
    (*_log) << "cause:" << cause <<endl;

    Problem problem(Problem::ERROR, cause, fileName, lineNumber, wordNumber);
    _problemLog->append(problem);
    _success=false;
}

void Assembler::throwWarning(QString fileName, int lineNumber, int wordNumber, QString cause){
    (*_log) << "WARNING" <<endl; 
    (*_log) << "File Name: " << fileName <<endl;
    (*_log) << "Line Number: " << lineNumber << " \tWord Number: " << wordNumber <<endl;
    (*_log) << "cause:" << cause <<endl;


    Problem warning(Problem::WARNING, cause, fileName, lineNumber,wordNumber);
    _problemLog->append(warning);
    _hasWarning = true;
}

void Assembler::writeHeader(){
    (*_log) << "Writing header" << endl;

    uint a = _endAddress & ~((1u<<16u)-1u);
    uint b = _endAddress & ((1u<<16u)-1u);
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

        (*_log) << "Header Token";
        for(QString token : preprocessed.tokens){
            (*_log) << token; 
        }
        (*_log) << endl;
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

        (*_log) << "Header Token";
        for(QString token : preprocessed.tokens){
            (*_log) << token; 
        }
        (*_log) << endl;

        _preprocessedQueue->insert(i++,preprocessed);
    }
}
