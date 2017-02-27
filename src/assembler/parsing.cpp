#include <iostream>
#include "utility.h"
#include "MachineCode.h"
#include "parsing.h" 
#include <QVector> 
#include "assembled.h"
#include <QtDebug>
#include <QTime>
#include "../architecture.h"

using namespace std;

void printError(Error error){
    qDebug() << "Line Number: " << error.lineNumber << " \tWord Number: " << error.wordNumber << endl;
    qDebug() << "cause:\n" << error.cause <<endl;
}

vector<int>* assemblyStringToInt(string assemblyString) {
    // Hammer-function for converting all arguments to numbers.
    // Returns two outputs: // -int value // -flag to indicate if this is an immediate

    vector<int>* result = new vector<int>();
    if(assemblyString.at(0) == 'R') {
        // Register
        result->push_back(stoi(assemblyString.substr(1)));
        result->push_back(0);
        return result;
    }
    if(assemblyString.at(0) == 'V') {
        // Vector
        result->push_back(16+(assemblyString.at(1)-'A'));
        result->push_back(0);
        return result;
    }
    if(assemblyString.at(0) == '#') {
        // Immediate
        if(assemblyString.substr(1,2) == "0X") {
            // Hex mode
            result->push_back(stoi(assemblyString.substr(3), NULL, 16));
        } else {
            // Maybe a decimal?
            result->push_back(stoi(assemblyString));
        }
        result->push_back(0);
        return result;
    }
    return NULL;
}

vector<int>* parseInstructionSCondition(string token) {
    // Retern a vector that has:
    // -Flag code
    // -opcode
    // -which operand decides the L bit? (-1 means none.)
    // -Then an alternation between start/end indexes for where tokens should be
    //  stored.
    // Much refactoring needed here.
    vector<int>* result = new vector<int>();
    /*
       if(token == "SEQ") {
       result->push_back(binaryStringToInt("1110"));
       result->push_back(binaryStringToInt("001101"));
       result->push_back(1);
       result->push_back(0);
       result->push_back(20);
       }
       else if(token == "CMP") {
       result->push_back(binaryStringToInt("1110"));
       result->push_back(binaryStringToInt("000010"));
       result->push_back(1);
       result->push_back(5);
       result->push_back(20);
       result->push_back(0);
       result->push_back(4);
       }
       else if(token == "CPY") {
       result->push_back(binaryStringToInt("1110"));
       result->push_back(binaryStringToInt("000100"));
       result->push_back(1);
       result->push_back(5);
       result->push_back(20);
       result->push_back(0);
       result->push_back(4);
       }
       else if(token == "LODLE") {
       result->push_back(binaryStringToInt("1010"));
       result->push_back(binaryStringToInt("000101"));
       result->push_back(1);
       result->push_back(5);
       result->push_back(20);
       result->push_back(0);
       result->push_back(4);
       }
       else {
    // Unrecognized instruction name
    return NULL;
    }
    */
    return result;
}

bool processLine(Preprocessed preprocessed ,QVector<uint>* instructions, QList<Error>* errorLog, SymbolTable* symTable) {

    int lineNumber = preprocessed.lineNumber;

    // Grab the opcode.
    QString instruction = preprocessed.tokens.at(0);
    preprocessed.tokens.removeFirst();
    QStringList operands = preprocessed.tokens;

    /*
    vector<int>* isc = parseInstructionSCondition(instruction);
    if(isc) {
        result->writeInt(isc->at(0), 28, 31);
        result->writeInt(isc->at(1), 22, 27);
        // Put in arguments.
        for(size_t i = 1; i < tokens.size(); i++) {
            vector<int>* asti = assemblyStringToInt(tokens.at(i));
            if(asti) {
                result->writeInt(asti->at(0), isc->at(3+2*(i-1)), isc->at(3+2*(i-1)+1));
                if(i == isc->at(2)) {
                    // This is the "Large" operand.
                    result->writeInt(asti->at(1), 21, 21);
                }
            }
            else {
                cout << "I don't know what " << tokens.at(i) << " is." << endl;
            }
        }
    }
    else {
        cout << "I don't know how to " << instruction << "." << endl;
    }

    //If succeed at processing line
    if(result == true){
        //Insert the instruction
        instructions.append(instruction);

        //append address and increment it
        addresses.append(address);

        qDebug() << "Instruction added: " << instruction << "\n";

    }
    */


    return true;
}

bool preprocessLine(int lineNumber, QString line, QVector<uint>* addresses, QVector<Preprocessed>* preprocesseds,QList<Error>* errorList, SymbolTable* symTable){
    //remove extra white space and comment
    line = line.trimmed().split(";").at(0).toUpper();
    qDebug() << "Preprocessing: " << line << endl;

    //If empty then continue
    if(line.isEmpty()){ 
        qDebug() << "SKIP: line is empty\n-" << endl;
    }

    //tokenize element in string
    QStringList tokens = line.split(QRegExp("\\s+"));

    for (int i = 0; i < tokens.size(); i++)
        qDebug() << tokens.at(i) << endl;

    // Bail if there's nothing here.
    if(tokens.size() == 0){
        qDebug() << "Is it even possible to have zero for tokens size?\n";
        exit(-1);
    }

    //get current address 
    uint currAddress;
    if(addresses->empty()){
        currAddress = 0;
    }
    else{
        currAddress = addresses->last() + INSTRUCTION_SIZE;
    }


    if(tokens.at(0).endsWith(":")){
        qDebug() << "Label detected" << endl;
        if(tokens.size() >= 1){
            Error error;
            error.lineNumber = lineNumber;
            error.wordNumber = 1;
            error.cause = "Invalid Format; Not a Label";
            printError(error);
            errorList->append(error);
            return false;
        }

        //remove : at the end of the string
        QString label = tokens.at(0).left(tokens.at(0).length()-1); 

        //check the validity of label name
        QRegExp re("^[a-zA-Z0-9_]*$");  
        if (!re.exactMatch(label)){
            Error error;
            error.lineNumber = lineNumber;
            error.wordNumber = 0;
            error.cause = "Invalid Format: " + label + " is not a Label";
            printError(error);
            errorList->append(error);
            return false;
        }

        //check whether label is already defined
        if(symTable->labelMap->contains(label)){
            Error error;
            error.lineNumber = lineNumber;
            error.wordNumber = 0;
            error.cause = "Invalid Format: " + label + " is already defined";
            printError(error);
            errorList->append(error);
            return false;
        }
        qDebug() << "Symbol added: " << label << " = " << currAddress << endl;
        symTable->labelMap->insert(label, currAddress);
        return true;
    }
    else{
        qDebug() << "Address added: " << currAddress << "\n";
        Preprocessed preprocessed;
        preprocessed.lineNumber = lineNumber;
        preprocessed.tokens = tokens;
        preprocesseds->append(preprocessed);
        addresses->append(currAddress);
        return true;
    }

}

/* Super method that convert string to Assembled
 *
 */
Assembled* processLines(QString lines)
{
    //Stupid constructor for Assembled class
    Assembled* assembled = new Assembled();

    //This will indicate whether we succeed at assembling the codes or not
    bool isSuccess = true;

    //create QVector to collect addresses and instructions
    QVector<uint> addresses;
    QVector<uint> instructions;

    //create QList to collect any errorlog
    QList<Error>* errorList = new QList<Error>();

    //create a symbol table and initialize it.
    SymbolTable symTable;
    symTable.labelMap = new QMap<QString, uint>();

    //Proprcessed stuff
    QVector<Preprocessed> preprocesseds;

    int lineNumber = 0;
    int address = 0;

    QTime timer;
    timer.start();

    qDebug() << "----------Start Assembly-------------" << endl;
    qDebug() << "Preprocessing" << endl;

    for(QString str  : lines.split("\n")){
        qDebug() << "Line: " << str << "\n";

        if(!preprocessLine(lineNumber, str,&addresses, &preprocesseds, errorList, &symTable)){
            isSuccess=false;
        }

        //increment line number by 1.
        lineNumber+=1;
        qDebug()<< "-\n";
    }

    for(Preprocessed preprocessed : preprocesseds){
        //process each line
        if(!processLine(preprocessed, &instructions, errorList, &symTable))
            isSuccess = false;

        qDebug()<< "-\n";
    }

    qDebug() << "Processing" <<endl;


    qDebug() << "----------Assembly Result---------------\n";
    qDebug() << "Elasped time: " << timer.elapsed() << " msec\n";

    //if we succeed to assemble, then remove error list
    if(isSuccess){
        qDebug() << "Success: true\n";
        assembled->isAssembled = true;
        assembled->assembly = new Assembly();
        assembled->assembly->nInstructions = instructions.size(); 
        assembled->assembly->instructions = instructions.data(); 
        assembled->assembly->nAddresses = addresses.size();
        assembled->assembly->addresses = addresses.data();
    }
    //else we failed to assemble, then remvoe assembly part
    else{
        qDebug() << "Success: false\n";
        assembled->isAssembled = false;
        assembled->errorList = errorList;
    }
    return assembled;
}


