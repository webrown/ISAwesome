#include "MainWindow.h"

MainWindow::MainWindow( QWidget *parent ): QMainWindow( parent ),settings("CS535","PISA")
{
    qDebug() << "MainWindow starts...";
    _ui.setupUi( this );

    //move assembly to different thread
    assembler = new Assembler();
    disassembler = new Disassembler();
    computer = new Computer();

    assembler->moveToThread(&assemblyThread);
    connect(&assemblyThread, &QThread::finished, assembler, &QObject::deleteLater);
    connect(this, &MainWindow::startBuild, assembler, &Assembler::assemble);
    connect(assembler, &Assembler::resultReady, this, &MainWindow::finishAssemble);
    assemblyThread.start();

    //add element on toolbar
    QSpinBox* cycleSpinBox = new QSpinBox();
    cycleSpinBox->setPrefix("Cycle: ");
    cycleSpinBox->setValue(1);
    cycleSpinBox->setRange(0,1000);
    _ui.toolBar->insertWidget(_ui.actionforward,cycleSpinBox);

    QSpinBox* pcSpinBox = new HexSpinBox(false);
    pcSpinBox->setPrefix("PC: ");
    pcSpinBox->setValue(0);
    _ui.toolBar->addWidget(pcSpinBox);

    //disable both undo and redo
    _ui.actionUndo->setEnabled(false);
    _ui.actionRedo->setEnabled(false);

    //Set filesystemview
    QFileSystemModel* fModel = new QFileSystemModel(this);
    fModel->setRootPath(settings.value("general/workdirectory",getDocDir()).toString());
    _ui.fileSystemView->setModel(fModel);
    _ui.fileSystemView->header()->hide();
    _ui.fileSystemView->setColumnHidden( 1, true );
    _ui.fileSystemView->setColumnHidden( 2, true );
    _ui.fileSystemView->setColumnHidden( 3, true );

    qDebug() << "MainWindow is initialized...";
}

MainWindow::~MainWindow()
{
    qDebug() << "Killing MainWindow";
    delete computer;
    delete assembler;
    delete disassembler;
    assemblyThread.quit();
    assemblyThread.wait();
    qDebug() << "Fin.";
}


//handle New Event
void MainWindow::handleNewButton(){
    qDebug() << "New Button is clicked!";
    NewFileDialog dialog(settings.value("general/workdirectory",getDocDir()).toString(),this);
    if(dialog.exec() != QDialog::Accepted){
        return;
    }
    QString str = dialog.getFileName();
    CodeEditor* widget = _ui.editorTab->newTab(str);

    connect(widget, SIGNAL(undoAvailable(bool)), this, SLOT(updateUndo(bool)));
    connect(widget, SIGNAL(redoAvailable(bool)), this, SLOT(updateRedo(bool)));
    qDebug() << str ;
    printlnConsole(str + " is opened");

}

//handle Open Event
void MainWindow::handleOpenButton()
{
    qDebug() << "Open Button is clicked!";
    QString docLoc = settings.value("general/workdirectory",getDocDir()).toString();
    QStringList fileNames = QFileDialog::getOpenFileNames(
            this,
            "Open Files",
            docLoc,
            "Any");
    for(QString fileName : fileNames){
        CodeEditor* widget = _ui.editorTab->openTab(fileName);
        connect(widget, SIGNAL(undoAvailable(bool)), this, SLOT(updateUndo(bool)));
        connect(widget, SIGNAL(redoAvailable(bool)), this, SLOT(updateRedo(bool)));
        printlnConsole(fileName + " is opened");
    }
}

//handle Save event
void MainWindow::handleSaveButton()
{
    qDebug() << "Save button is clicked";
    if(_ui.editorTab->saveTab()){
        printlnConsole(_ui.editorTab->currentEditor()->sourceFile->fileName() + " is saved");
    }
    else{
        printlnConsole("save failed");
    }
}

void MainWindow::handleSaveAllButton()
{
    qDebug() << "Save all button is clicked";
    if(_ui.editorTab->saveAllTab()){
        for(int i =0; i < _ui.editorTab->count(); i++){
            printlnConsole(((CodeEditor*)_ui.editorTab->widget(i))->sourceFile->fileName() + " is saved");
        }
    }
    else{
        printlnConsole("save failed");
    }
}

//handle Save As event
void MainWindow::handleSaveAsButton()
{
    qDebug() << "Save As button is clicked";
    NewFileDialog dialog(settings.value("general/workdirectory",getDocDir()).toString(),this);
    int result = dialog.exec();
    if(result != QDialog::Accepted){
        return;
    }
    QString str = dialog.getFileName();
    if(_ui.editorTab->saveAsTab(str)){
        printlnConsole(_ui.editorTab->currentEditor()->sourceFile->fileName()+ str.section("/",-1,-1));
    }
    else{
        printlnConsole("save failed");
    }
}

//handle Undo Event
void MainWindow::handleUndoButton()
{
    qDebug() << "Undo button is clicked";

    ((CodeEditor*)_ui.editorTab->currentWidget())->undo();
}

void MainWindow::handleRedoButton()
{
    qDebug() << "Redo button is clicked";
    ((CodeEditor*)_ui.editorTab->currentWidget())->redo();
}

//hande about pisa event
void MainWindow::handleAboutPISAButton()
{
    qDebug() << "About PISA button is clicked";
    QString link = "https://github.com/webrown/PISA";
    QDesktopServices::openUrl(QUrl(link));
}


void MainWindow::handleAddCache(){ 
    qDebug() << "Add Cache button is clicked";
    NewCacheDialog dialog(computer->topCache, this);
    int result = dialog.exec();
    if(result == QDialog::Accepted){
        CacheInfo info = dialog.getCacheInfo();
        Cache* cache = new Cache(info.indexBits, info.logDataWordCount, info.logAssociativity,info.delay, info.next);
        cache->prevCache = info.prev;
        if(info.next != NULL){
                info.next->prevCache = cache;
        }
        if(info.prev != NULL){
            info.prev->nextCache = cache;
        }
        else{
            computer->topCache = cache;
        }
        _ui.tabWidget_memory->addTab(new CacheView(cache), "AAA");

        int index = 1;
        for(Cache* curr = computer->topCache; curr != NULL; curr = curr->nextCache){
            _ui.tabWidget_memory->setTabText(_ui.tabWidget_memory->indexOf(curr->view),(new QString("Cache %1(BOTH)"))->arg(index++));
        }   
    }
}

void MainWindow::handleRemoveCache(){
    qDebug() << "Remove Cache button is clicked";
}

void MainWindow::handleClearCache(){
    qDebug() << "Clear Cache button is clicked";
} 
void MainWindow::handleFlushCache(){
    qDebug() << "Flush Cache button is clicked";
}

void MainWindow::handleFlushAllCache(){
    qDebug() << "Flush All cache button is clicked";
}
void MainWindow::handleBuild(){
    qDebug() << "Build button is clicked";
    //Nothing to build
    //TODO output?
    int index = _ui.editorTab->currentIndex();
    if(index == -1){ 
        _ui.consoleTextEdit->appendPlainText("Nothing to build...");
        return;
    }
    //Save file: I don't know but eclipse does this, so I guess there is some reason why we need to save file before assembly

   assemble(_ui.editorTab->currentEditor()->sourceFile->fileName(), false); 
}

void MainWindow::assemble(QString fileName, bool runAfter){
    handleSaveButton();
    AssemblerConfiguration config;
    config.useDefaultMacro = settings.value("assembly/useDefaultMacro", true).toBool();
    config.useDefaultAlias = settings.value("assembly/useDefaultAlias", true).toBool();
    config.useGlobalMacro = settings.value("assembly/useGlobalMacro", true).toBool();
    config.useGlobalAlias = settings.value("assembly/useGlobalAlias", true).toBool();
    config.useMainEntry = settings.value("assembly/useMainEntry", true).toBool();
    config.useWall =  settings.value("assembly/useWall", true).toBool();
   
    startBuild(fileName, config, runAfter);
}
void MainWindow::finishAssemble(Assembled* assembled, bool runAfter){
    clearConsole();
    //remove this
    _ui.tracker->clear();
    displayProblems(assembled->problemLog);

    bool isAssembled = assembled->isAssembled;
    QString fileName = assembled->fileName;
    if(isAssembled == true){
        printlnConsole("Build succeeded.");
        ProgramManagerX::saveProgram(fileName +".out", assembled->instructions);
        printlnConsole(fileName + " is saved.");
    }
    else{
        printlnConsole("Build failed...");
    }

    printlnConsole("Time elasped: " + QString::number(assembled->elaspedTime) + " msec");
    delete assembled;
    if((isAssembled & runAfter) == true){
        launchProgram(fileName + ".out");
    }
}

void MainWindow::displayProblems(QList<Problem>* problemLog){
    //Clear problem view
    _ui.problemTable->clearContents();
    _ui.problemTable->setRowCount(problemLog->size());

    for(int i =0; i < problemLog->size(); i++){
        Problem problem = problemLog->at(i);
        QString type = (problem.type == WARNING ? "Warning" :(problem.type == ERROR ? "Error" : "???"));
        _ui.problemTable->setItem(i,0,new QTableWidgetItem(type));
        _ui.problemTable->setItem(i,1,new QTableWidgetItem(problem.fileName));
        _ui.problemTable->setItem(i,2,new QTableWidgetItem(QString::number(problem.lineNumber+1)));
        _ui.problemTable->setItem(i,3,new QTableWidgetItem(QString::number(problem.wordNumber+1)));
        _ui.problemTable->setItem(i,4,new QTableWidgetItem(problem.cause));
    }
}
void MainWindow::handleBuildAll(){
    qDebug() << "Build All button is clicked";
}

void MainWindow::handlePreference(){
    qDebug() << "Preference button is clicked";
    PreferenceDialog dialog(this);
    dialog.exec();
}

void MainWindow::handleForward(){
}
void MainWindow::handleBackward(){
}
void MainWindow::handlePlay(){
    qDebug() << "Run button is clicked";
    //Nothing to build
    //TODO output?
    if(_ui.editorTab->isEmpty()){ 
        _ui.consoleTextEdit->appendPlainText("Nothing to build...");
        return;
    }
    if(shouldIAssemble() == true){
        qDebug() << "Well, I guess I have to assemble then";
        QString fileName = _ui.editorTab->currentEditor()->sourceFile->fileName() ;
        assemble(fileName, true);
    }
    else{
        qDebug() << "HA, no assemble";
        QString fileName = _ui.editorTab->currentEditor()->sourceFile->fileName() + ".out";
        launchProgram(fileName);
    }
}

void MainWindow::launchProgram(QString fileName){
    clearConsole();
    printlnConsole("Run: " + fileName);
    QVector<uint>* instructions = ProgramManagerX::loadProgram(fileName);
    //change this code
    _ui.tracker->clear();
    for(int i = 0; i < instructions->size(); i++){
        QString address = QString::number(INSTRUCTION_SIZE  * i,16).rightJustified(8, '0');
        QString instruction =disassembler->disassemble(instructions->at(i)); 
        _ui.tracker->addItem(address + "\t" + instruction);
        
    }
}

bool MainWindow::shouldIAssemble(){
    QString fileName = _ui.editorTab->currentEditor()->sourceFile->fileName();
    QString outputFileName = fileName + ".out"; 
    QFile outputFile(outputFileName);
    if(outputFile.exists() == false){
        qDebug() << "1";
        return true;
    }
    QFileInfo outputFileInfo(outputFile);
    QFileInfo sourceFileInfo(*(_ui.editorTab->currentEditor()->sourceFile));
    if(outputFileInfo.lastModified() < sourceFileInfo.lastModified()){
        qDebug() << "2";

        return true;
    }
    if(_ui.editorTab->isCurrentSaved() == false){
        qDebug() << "3";

        return true;
    }
    return false;
}
void MainWindow::handlePause(){
}
void MainWindow::handleStop(){
}

//update undo button
void MainWindow::updateUndo(bool avail)
{
    _ui.actionUndo->setEnabled(avail);
}

//update redo button
void MainWindow::updateRedo(bool avail)
{
    _ui.actionRedo->setEnabled(avail);
}

void MainWindow::printConsole(QString line){
    qDebug() << "Printed on console: " << line ;
    _ui.tabWidget_output->setCurrentWidget(_ui.tab_console);
    _ui.consoleTextEdit->insertPlainText(line);
}
void MainWindow::printlnConsole(QString line){
    qDebug() << "Printed with line on console: " << line;
    _ui.tabWidget_output->setCurrentWidget(_ui.tab_console);
    _ui.consoleTextEdit->appendPlainText(line);
}
void MainWindow::clearConsole(){
    qDebug() << "Clear Console";
    _ui.tabWidget_output->setCurrentWidget(_ui.tab_console);
    _ui.consoleTextEdit->clear();
}
