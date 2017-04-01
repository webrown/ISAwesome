#include "MainWindow.h"

MainWindow::MainWindow( QWidget *parent ): QMainWindow( parent ),settings("CS535","PISA") ,container(0, true)
{
    qRegisterMetaType<ThreadMessage>();
    qDebug() << "GUI: MainWindow starts...";
    //Set up gui
    _ui.setupUi( this );

    //move assembly to different thread 
    assembler = new Assembler();
    computer = new Computer();

    //make threads
    qDebug() << "GUI: Creating Assembly thread";
    assemblyThread = new QThread(this); assembler->moveToThread(assemblyThread);
    connect(assemblyThread, &QThread::finished, assembler, &QObject::deleteLater);
    connect(this, &MainWindow::startBuild, assembler, &Assembler::assemble);
    connect(assembler, &Assembler::resultReady, this, &MainWindow::finishAssemble);
    assemblyThread->start();

    qDebug() <<"GUI: Creating Computer thread";
    computerThread = new QThread(this);
    computer->moveToThread(computerThread);
    connect(computerThread, &QThread::finished, computer, &QObject::deleteLater);
    connect(this, &MainWindow::_sendMessage, computer, &Computer::procMessage);
    connect(computer, &Computer::sendMessage, this, &MainWindow::procMessage);
    computerThread->start();

    //add element on toolbar
    cycleSpinBox = new QSpinBox(this);
    cycleSpinBox->setPrefix("Cycle: ");
    cycleSpinBox->setValue(1);
    cycleSpinBox->setRange(0,1000);
    _ui.toolBar->insertWidget(_ui.actionforward,cycleSpinBox);

    pcSpinBox = new MyQSpinBox(this);
    pcSpinBox->setPrefix("PC: ");
    pcSpinBox->setValue(0);
    pcSpinBox->setSingleStep(INSTRUCTION_SIZE);
    _ui.toolBar->addWidget(pcSpinBox);
    connect(pcSpinBox, SIGNAL(valueChangedNotBySet(int)) ,this, SLOT(handleUpdatePC(int)));
    
    delayBox = new QDoubleSpinBox(this);
    delayBox->setValue(.5);
    delayBox->setRange(0,1);
    delayBox->setPrefix("Delay: ");
    delayBox->setSingleStep(0.1);
    _ui.toolBar->insertWidget(_ui.actionRun,delayBox);

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
    QModelIndex idx = fModel->index(settings.value("general/workdirectory",getDocDir()).toString());
    _ui.fileSystemView->setRootIndex(idx);

    _ui.tab_memory->init(this,_ui.tableWidget_memory,_ui.spinBox,_ui.pushButton, _ui.lineEdit);
    _ui.tab_register->init(this,_ui.tableWidget_6,_ui.comboBox);
    _ui.tab_cache->init(this,_ui.tableWidget_7,_ui.cacheListBox, _ui.pushButton_2, _ui.tagLine, _ui.indexLine, _ui.offsetLine, _ui.nextButton ,_ui.prevButton);
    _ui.tracker->init(this);


    updateByState(Computer::DEAD);
    qDebug() << "GUI: MainWindow is initialized...";
}

MainWindow::~MainWindow()
{
    qDebug() << "GUI: Killing MainWindow";
    _sendMessage(ThreadMessage(ThreadMessage::R_STOP, {}));
    assemblyThread->quit();
    assemblyThread->wait();
    computerThread->quit();
    computerThread->wait();
    qDebug() << "GUI: Fin.";
}

void MainWindow::updateNavigation(){
    qDebug() << "GUI: Update navigation";
    QFileSystemModel* fModel = (QFileSystemModel*) _ui.fileSystemView->model();
    fModel->setRootPath(settings.value("general/workdirectory",getDocDir()).toString());
    _ui.fileSystemView->setModel(fModel);
    QModelIndex idx = fModel->index(settings.value("general/workdirectory",getDocDir()).toString());
    _ui.fileSystemView->setRootIndex(idx);
}


//handle New Event
void MainWindow::handleNew(){
    qDebug() << "GUI: New Button is clicked!";
    NewFileDialog dialog(settings.value("general/workdirectory",getDocDir()).toString(),this);
    if(dialog.exec() != QDialog::Accepted){
        return;
    }
    QString str = dialog.getFileName();
    CodeEditor* widget = _ui.editorTab->newTab(str);
    connect(widget, SIGNAL(undoAvailable(bool)), this, SLOT(updateUndo(bool)));
    connect(widget, SIGNAL(redoAvailable(bool)), this, SLOT(updateRedo(bool)));
    printlnConsole(str + " is opened");
}

//handle Open Event
void MainWindow::handleOpen()
{
    qDebug() << "GUI: Open Button is clicked!";
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

void MainWindow::handleOpenFromNavigation(QModelIndex index){
    qDebug() << "GUI: Open from navigation";
    QString fileName = ((QFileSystemModel*)_ui.fileSystemView->model())->rootPath() + "/"+ index.data().toString();
    QFile file(fileName);
    QFileInfo fileInfo(file);
    qDebug() << fileName;

    //It's directory, do not open it.
    if(file.exists() == false || fileInfo.isDir() == true){
        return;
    }
    CodeEditor* widget = _ui.editorTab->openTab(fileName);
    connect(widget, SIGNAL(undoAvailable(bool)), this, SLOT(updateUndo(bool)));
    connect(widget, SIGNAL(redoAvailable(bool)), this, SLOT(updateRedo(bool)));
    printlnConsole(fileName + " is opened");
}

//handle Save event
void MainWindow::handleSave()
{
    qDebug() << "GUI: Save button is clicked";
    if(_ui.editorTab->saveTab()){
        printlnConsole(_ui.editorTab->currentEditor()->sourceFile->fileName() + " is saved");
    }
    else{
        printlnConsole("save failed");
    }
}

void MainWindow::handleSaveAll()
{
    qDebug() << "GUI: Save all button is clicked";
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
void MainWindow::handleSaveAs()
{
    qDebug() << "GUI: Save As button is clicked";
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
void MainWindow::handleUndo()
{
    qDebug() << "GUI: Undo button is clicked";
    ((CodeEditor*)_ui.editorTab->currentWidget())->undo();
}

void MainWindow::handleRedo()
{
    qDebug() << "GUI: Redo button is clicked";
    ((CodeEditor*)_ui.editorTab->currentWidget())->redo();
}


//hande about pisa event
void MainWindow::handleAboutPISA()
{
    qDebug() << "GUI: About PISA button is clicked";
    QString link = "https://github.com/webrown/PISA";
    QDesktopServices::openUrl(QUrl(link));
}

void MainWindow::handleAddCache(){ 
    qDebug() << "GUI: Add Cache button is clicked";
    NewCacheDialog dialog(&container, this);
    int result = dialog.exec();
    if(result == QDialog::Accepted){
        qDebug() << "GUI: Adding a cache";
        printlnConsole("Cache added...");
        MemoryStructure::setUpPlz(_ui.cacheListBox, &container);
        QList<QVariant> toSend;
        toSend << container._lastAdded->next->id;
        toSend << container._lastAdded->type;
        toSend << container._lastAdded->indexBits;
        toSend << container._lastAdded->logDataWordCount;
        toSend << container._lastAdded->logAssociativity;
        toSend << container._lastAdded->delay;
        sendMessage(ThreadMessage(ThreadMessage::R_ADD_CACHE, toSend));
        updateMemoryWidget();
   }
}

void MainWindow::handleRemoveCache(){
    qDebug() << "Remove Cache button is clicked";
    if(_ui.tabWidget_memory->currentWidget() != _ui.tab_cache || _ui.cacheListBox->count() == 0){
        QMessageBox msgBox;
        msgBox.critical(0, "Error", "No cache is selected");
        return;
    }
    container.removeCache(_ui.cacheListBox->currentData().toInt());
    MemoryStructure::setUpPlz(_ui.cacheListBox, &container);
    sendMessage(ThreadMessage(ThreadMessage::R_REMOVE_CACHE, container._lastAdded->id));
    updateMemoryWidget();

}


void MainWindow::handleClearCache(){
    /* qDebug() << "Clear Cache button is clicked"; */
    // printlnConsole("Cache cleared");
    // Cache* nextCache;
    // for(Cache* cache = computer->topCache; cache != NULL; cache = nextCache){
    //     CacheView* cacheView =cache->view;
    //
    //     _ui.tabWidget_memory->removeTab(_ui.tabWidget_memory->indexOf(cacheView));
    //
    //     nextCache = cache->nextCache;
    //     delete cache;
    //     delete cacheView;
    // }
    /* computer->topCache =NULL; */
} 

void MainWindow::handleBuild(){
    qDebug() << "GUI: Build button is clicked";
    //Nothing to build
    if(_ui.editorTab->isEmpty() == true){ 
        _ui.consoleTextEdit->appendPlainText("Nothing to build...");
        return;
    }
    //Save file: I don't know but eclipse does this, so I guess there is some reason why we need to save file before assembly
    _ui.editorTab->currentEditor()->clearMarks();
    assemble(_ui.editorTab->currentEditor()->sourceFile->fileName(), false); 
}

void MainWindow::handleBuildAll(){
    qDebug() << "GUI: Build All button is clicked";
    printlnConsole("Not implemented");
}

void MainWindow::assemble(QString fileName, bool runAfter){
    qDebug() << "GUI: assemble requested";
    handleSaveAll();
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
    qDebug() << "GUI: finishing assembly";

    clearConsole();

    displayProblems(assembled->problemLog);

    //Get variables
    bool isAssembled = assembled->isAssembled;
    QString fileName = assembled->fileName;
    if(isAssembled == true){
        printlnConsole("Build succeeded.");
        ProgramManagerX::saveProgram(fileName +".out", assembled->program);
        printlnConsole(fileName + " is saved.");
    }
    else{
        printlnConsole("Build failed...");
    }
    printlnConsole("Log file generated: ");

    printlnConsole("Time elasped: " + QString::number(assembled->elaspedTime) + " msec");
    //Clean assembled
    delete assembled;
    if(isAssembled  == true && runAfter == true){
        uploadProgram(fileName + ".out");
    }
}

void MainWindow::displayProblems(QList<Problem>* problemLog){
    qDebug() << "GUI: Display problems from assembly";
    //Clear problem view
    _ui.problemTable->clearContents();
    _ui.problemTable->setRowCount(problemLog->size());

    QMultiMap<QString, Problem> problemMap;

    for(int i =0; i < problemLog->size(); i++){
        Problem problem = problemLog->at(i);
        problemMap.insert(problem.fileName, problem);
        QString type = (problem.type == Problem::WARNING ? "Warning" :(problem.type == Problem::ERROR ? "Error" : "???"));
        _ui.problemTable->setItem(i,0,new QTableWidgetItem(type));
        _ui.problemTable->setItem(i,1,new QTableWidgetItem(problem.fileName));
        _ui.problemTable->setItem(i,2,new QTableWidgetItem(QString::number(problem.lineNumber+1)));
        _ui.problemTable->setItem(i,3,new QTableWidgetItem(QString::number(problem.wordNumber+1)));
        _ui.problemTable->setItem(i,4,new QTableWidgetItem(problem.cause));
    }

    for(QString fileName : problemMap.keys()){
        struct {
            bool operator()(Problem a, Problem b){   
                return a.lineNumber < b.lineNumber;
            }   
        } compare;
        QList<Problem> problems = problemMap.values(fileName);
        std::sort(problems.begin(), problems.end(), compare);
        for(int i =0; i < _ui.editorTab->count(); i++){
            CodeEditor* editor = (CodeEditor*)_ui.editorTab->widget(i);
            if(editor->sourceFile->fileName() == fileName){
                editor->mark(problems);
            }
        }
    }
}


void MainWindow::handlePreference(){
    qDebug() << "GUI: Preference button is clicked";
    PreferenceDialog dialog(this);
    dialog.exec();
    updateNavigation();
}

void MainWindow::handleUpload(){
    qDebug() << "GUI: Upload button is clicked";
    //Nothing to build
    if(_ui.editorTab->isEmpty() == true){ 
        printlnConsole("Nothing to build...");
        return;
    }

    //check whether assemble or not
    if(shouldIAssemble() == true){
        qDebug() << "GUI: assemble and then upload";
        QString fileName = _ui.editorTab->currentEditor()->sourceFile->fileName() ;
        assemble(fileName, true);
    }
    else{
        qDebug() << "GUI: just upload";
        QString fileName = _ui.editorTab->currentEditor()->sourceFile->fileName() + ".out";
        uploadProgram(fileName);
    }
}

bool MainWindow::shouldIAssemble(){
    //Check file exists or not
    QString fileName = _ui.editorTab->currentEditor()->sourceFile->fileName();
    QFile outputFile(fileName + ".out");
    //If output doesn't exists, then assemble
    if(outputFile.exists() == false){
        qDebug("GUI: assemble since output file doesn't exist");
        return true;
    }

    //Check the timestamp of output files
    QFileInfo outputFileInfo(outputFile);
    QFileInfo sourceFileInfo(*(_ui.editorTab->currentEditor()->sourceFile));
    if(outputFileInfo.lastModified() < sourceFileInfo.lastModified()){
        qDebug() << "GUI: assemble since file is modified";
        return true;
    }

    //Check whether tab is saved or not
    if(_ui.editorTab->isCurrentSaved() == false){
        qDebug() << "GUI: assebmle since current file is not saved";
        return true;
    }
    return false;
}

void MainWindow::uploadProgram(QString fileName){
    qDebug() << "GUI: launch Program";
    printlnConsole("Run: " + fileName);


    //Computer will do this job now on
    // QList<uint> instructions = ProgramManagerX::loadProgram(fileName);

    // QList<QVariant> _instructions;
    // for(uint x : instructions){
    //     _instructions.append(x);
    // } 

    //TODO move this
    /* _ui.tracker->clear(); */
    /* _ui.tracker->feed(_instructions); */
    sendMessage(ThreadMessage(ThreadMessage::R_INIT,fileName));
}


void MainWindow::handleForward(){
   qDebug() << "GUI: Forward button is clicked"; 
   int cycles = cycleSpinBox->value();
   sendMessage(ThreadMessage(ThreadMessage::R_STEP, {cycles}));
}

void MainWindow::handlePlay(){
    qDebug() << "GUI: Play button is clicked";
    sendMessage(ThreadMessage(ThreadMessage::R_STEP, {-1}, {delayBox->value()}));
}

void MainWindow::handleBackward(){
    qDebug() << "GUI: Backward button is clicked";
    printlnConsole("dS > dQ/T");
}

void MainWindow::handlePause(){
    qDebug() << "GUI: Pause button is clicked";
    sendMessage(ThreadMessage(ThreadMessage::R_PAUSE, {}));
}
void MainWindow::handleStop(){
    sendMessage(ThreadMessage(ThreadMessage::R_STOP, {}));
}

void MainWindow::printConsole(QString line){
    qDebug() << "GUI: console: " << line ;
    _ui.tabWidget_output->setCurrentWidget(_ui.tab_console);
    _ui.consoleTextEdit->insertPlainText(line);
}
void MainWindow::printlnConsole(QString line){
    qDebug() << "GUI: console: " << line;
    _ui.tabWidget_output->setCurrentWidget(_ui.tab_console);
    _ui.consoleTextEdit->appendPlainText(line);
}
void MainWindow::clearConsole(){
    qDebug() << "GUI: Clear Console";
    _ui.tabWidget_output->setCurrentWidget(_ui.tab_console);
    _ui.consoleTextEdit->clear();
}


void MainWindow::handleErrorFromComputer(QString errorMessage){
    QMessageBox msgBox;
    msgBox.critical(0,"Error",errorMessage);
}

void MainWindow::procMessage(ThreadMessage message){
    ThreadMessage::Type type = message.type;
    QVariant info = message.message;
    switch(message.type){
        case ThreadMessage::A_STATE_CHANGE:
            qDebug() << "GUI: RECV FROM COMPUTER: A_STATE_CHANGE";
            updateByState(static_cast<Computer::State>(info.toInt()));
            return;
        case ThreadMessage::A_UPDATE:
            qDebug() << "GUI: RECV FROM COMPUTER: A_UPDATE";
            update(info.toUInt());
            return;
        case ThreadMessage::A_FEED:
            qDebug() << "GUI: RECV FROM COMPUTER: A_FEED";
            _ui.tracker->clear();
            _ui.tracker->feed(info.toList());
            return;
        case ThreadMessage::A_SET_PC:
            qDebug() << "GUI: RECV FROM COMPUTER: A_SET_PC";
            updateMemoryWidget();
            break;
        case ThreadMessage::A_OKAY:
            qDebug() << "GUI: RECV FROM COMPUTER: A_OKAY";
            //Do nothing
            break;
        case ThreadMessage::A_ERROR:
            qDebug() << "GUI: RECV FROM COMPUTER: A_ERROR";
            handleErrorFromComputer(info.toString());
            break;
        case ThreadMessage::A_VIEW_MEMORY:
            qDebug() << "GUI: RECV FROM COMPUTER: A_VIEW_MEMORY";
            _ui.tab_memory->display(info.toList());
            break;
        case ThreadMessage::A_VIEW_CACHE:
            qDebug() << "GUI: RECV FROM COMPUTER: A_VIEW_CACHE";
            _ui.tab_cache->display(info.toList());
            break;
        case ThreadMessage::A_VIEW_REGISTER:
            qDebug() << "GUI: RECV FROM COMPUTER: A_VIEW_REGISTER";
            _ui.tab_register->display(info.toList());
            break;
        case ThreadMessage::A_SAVE_STATE:
            qDebug() << "GUI: RECV FROM COMPUTER: A_SAVE_STATE";
            break;
        case ThreadMessage::A_RESTORE_STATE:
            qDebug() << "GUI: RECV FROM COMPUTER: A_RESTORE_STATE";
            break;
        case ThreadMessage::A_VIEW_PERFORMANCE:
            qDebug() << "GUI: RECV FROM COMPUTER: A_VIEW_PERFORMANCE";
            _ui.treeWidget->display(info.toMap());
            break;
        default:
            qDebug() << "GUI: Invalid message";
            exit(-1);
            break;
    }
    messageQueue.dequeue();
    if(messageQueue.isEmpty() == false){
        emit _sendMessage(messageQueue.head());
    }
}
void MainWindow::updateByState(Computer::State state){
    switch(state){
        case Computer::DEAD:
            _ui.actionUpload->setEnabled(true);
            _ui.actionRun->setEnabled(false);
            _ui.actionpause->setEnabled(false);
            _ui.actionstop->setEnabled(false);
            _ui.actionforward->setEnabled(false);
            _ui.actionSave_state->setEnabled(false);
            _ui.actionRestore_State->setEnabled(true);
            _ui.actionAddCache->setEnabled(true);
            _ui.actionRemoveCache->setEnabled(true);
            _ui.actionClearCache->setEnabled(true);

            break;
        case Computer::RUNNING:
            _ui.actionUpload->setEnabled(false);
            _ui.actionRun->setEnabled(false);
            _ui.actionpause->setEnabled(true);
            _ui.actionstop->setEnabled(true);
            _ui.actionforward->setEnabled(false);
            _ui.actionSave_state->setEnabled(false);
            _ui.actionRestore_State->setEnabled(false);
            _ui.actionAddCache->setEnabled(false);
            _ui.actionRemoveCache->setEnabled(false);
            _ui.actionClearCache->setEnabled(false);


            break;
        case Computer::PAUSED:
            _ui.actionUpload->setEnabled(false);
            _ui.actionRun->setEnabled(true);
            _ui.actionpause->setEnabled(false);
            _ui.actionstop->setEnabled(true);
            _ui.actionforward->setEnabled(true);
            _ui.actionSave_state->setEnabled(true);
            _ui.actionRestore_State->setEnabled(false);
            _ui.actionAddCache->setEnabled(false);
            _ui.actionRemoveCache->setEnabled(false);
            _ui.actionClearCache->setEnabled(false);


            break;
    }
}
void MainWindow::update(uint pc){
    qDebug() << "GUI: FULL ON UPDATE";
    pcSpinBox->setHexValue(pc);
    updateMemoryWidget();
    _ui.tracker->mark(pc/INSTRUCTION_SIZE);
    if(_ui.leftBoard->currentWidget() == _ui.tab_performance){
        sendMessage(ThreadMessage(ThreadMessage::R_VIEW_PERFORMANCE,{}));
    }
}
void MainWindow::sendMessage(ThreadMessage message){
    qDebug() << "GUI: send message";
    //If queue is empty, send right away
    if(messageQueue.isEmpty()){
        messageQueue.enqueue(message);
        emit _sendMessage(message);
    }
    else{
        messageQueue.enqueue(message);
    }
}

void MainWindow::handleUpdatePC(int v){
    qDebug() << "GUI: update pc through spinbox";
    sendMessage(ThreadMessage(ThreadMessage::R_SET_PC, {pcSpinBox->hexValue()}));
}
void MainWindow::updateMemoryWidget(){
    QWidget* widget = _ui.tabWidget_memory->currentWidget();
    if(widget == _ui.tab_register){
        _ui.tab_register->update();
    }
    else if (widget == _ui.tab_cache){
        // _ui.tab_register->update();
        _ui.tab_cache->update();
    }
    else if (widget == _ui.tab_memory){
        _ui.tab_memory->update();
    }

}
void MainWindow::handleSaveState(){
    qDebug() << "GUI: save state";
    QString docLoc = settings.value("general/workdirectory",getDocDir()).toString();
    QString fileName = QFileDialog::getSaveFileName(
            this,
            "Save state",
            docLoc,
            "State (*.state)");
    qDebug() << fileName;
    sendMessage(ThreadMessage(ThreadMessage::R_SAVE_STATE, {fileName}));
}
void MainWindow::handleRestoreState(){
    qDebug() << "GUI: restore state";
    QString docLoc = settings.value("general/workdirectory",getDocDir()).toString();
    QString fileName = QFileDialog::getOpenFileName(
            this,
            "Open state",
            docLoc,
            "State (*.state)");
    qDebug() << fileName;

    sendMessage(ThreadMessage(ThreadMessage::R_RESTORE_STATE, fileName));
}

