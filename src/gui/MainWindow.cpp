#include "MainWindow.h"

MainWindow::MainWindow( QWidget *parent ): QMainWindow( parent ),settings("CS535","PISA")
{
    qRegisterMetaType<ThreadMessage>();
    qDebug() << "MainWindow starts...";
    _ui.setupUi( this );
//move assembly to different thread 
    assembler = new Assembler();
    disassembler = new Disassembler();
    computer = new Computer();
assemblyThread = new QThread(this); assembler->moveToThread(assemblyThread);
    connect(assemblyThread, &QThread::finished, assembler, &QObject::deleteLater);
    connect(this, &MainWindow::startBuild, assembler, &Assembler::assemble);
    connect(assembler, &Assembler::resultReady, this, &MainWindow::finishAssemble);
    assemblyThread->start();

    computerThread = new QThread(this);
    computer->moveToThread(computerThread);
    connect(computerThread, &QThread::finished, computer, &QObject::deleteLater);
    connect(this, &MainWindow::_sendMessage, computer, &Computer::procMessage);
    connect(computer, &Computer::sendMessage, this, &MainWindow::procMessage);

    computerThread->start();

    //add element on toolbar
    QSpinBox* cycleSpinBox = new QSpinBox(this);
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
    QModelIndex idx = fModel->index(settings.value("general/workdirectory",getDocDir()).toString());
    _ui.fileSystemView->setRootIndex(idx);

    _ui.tab_memory->init(this,_ui.tableWidget_memory,_ui.spinBox,_ui.pushButton, _ui.lineEdit);
    _ui.tab_register->init(this,_ui.tableWidget_6,_ui.comboBox);


    qDebug() << "MainWindow is initialized...";
}

MainWindow::~MainWindow()
{
    qDebug() << "Killing MainWindow";
    assemblyThread->quit();
    assemblyThread->wait();
    computerThread->quit();
    computerThread->wait();
    qDebug() << "Fin.";
}

void MainWindow::updateNavigation(){
    QFileSystemModel* fModel = (QFileSystemModel*) _ui.fileSystemView->model();
    fModel->setRootPath(settings.value("general/workdirectory",getDocDir()).toString());
    _ui.fileSystemView->setModel(fModel);
    QModelIndex idx = fModel->index(settings.value("general/workdirectory",getDocDir()).toString());
    _ui.fileSystemView->setRootIndex(idx);
}


//handle New Event
void MainWindow::handleNew(){
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
void MainWindow::handleOpen()
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

void MainWindow::handleOpenFromNavigation(QModelIndex index){
    qDebug() << "Open from navigation";
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
    qDebug() << "Save button is clicked";
    if(_ui.editorTab->saveTab()){
        printlnConsole(_ui.editorTab->currentEditor()->sourceFile->fileName() + " is saved");
    }
    else{
        printlnConsole("save failed");
    }
}

void MainWindow::handleSaveAll()
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
void MainWindow::handleSaveAs()
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
void MainWindow::handleUndo()
{
    qDebug() << "Undo button is clicked";

    ((CodeEditor*)_ui.editorTab->currentWidget())->undo();
}

void MainWindow::handleRedo()
{
    qDebug() << "Redo button is clicked";
    ((CodeEditor*)_ui.editorTab->currentWidget())->redo();
}

//hande about pisa event
void MainWindow::handleAboutPISA()
{
    qDebug() << "About PISA button is clicked";
    QString link = "https://github.com/webrown/PISA";
    QDesktopServices::openUrl(QUrl(link));
}


void MainWindow::handleAddCache(){ 
    qDebug() << "Add Cache button is clicked";
/*     NewCacheDialog dialog(computer->topCache, this); */
    // int result = dialog.exec();
    // if(result == QDialog::Accepted){
    //     printlnConsole("Cache added");
    //     CacheInfo info = dialog.getCacheInfo();
    //     Cache* cache = new Cache(info.indexBits, info.logDataWordCount, info.logAssociativity,info.delay, info.next);
    //     cache->prevCache = info.prev;
    //     int _index = 1;
    //     if(info.next != NULL){
    //             info.next->prevCache = cache;
    //     }
    //     if(info.prev != NULL){
    //         _index = _ui.tabWidget_memory->indexOf(info.prev->view) + 1;
    //         info.prev->nextCache = cache;
    //     }
    //     else{
    //         computer->topCache = cache;
    //     }
    //     _ui.tabWidget_memory->insertTab(_index,new CacheView(cache), "Cache");
    //
    //     int index = 1;
    //     //reset name
    //     for(Cache* curr = computer->topCache; curr != NULL; curr = curr->nextCache){
    //         _ui.tabWidget_memory->setTabText(_ui.tabWidget_memory->indexOf(curr->view),(new QString("Cache %1(BOTH)"))->arg(index++));
    //     }
    // }
/*  */
}

void MainWindow::handleRemoveCache(){
/*     qDebug() << "Remove Cache button is clicked"; */
    // QWidget* widget = _ui.tabWidget_memory->currentWidget();
    // if(CacheView* cacheView = dynamic_cast<CacheView*>(widget)) {
    //     printlnConsole("Cache removed");
    //     Cache* cache = cacheView->cache;
    //     Cache* prevCache = cache->prevCache;
    //     Cache* nextCache = cache->nextCache;
    //     if(prevCache != NULL && nextCache != NULL){
    //         prevCache->nextCache = nextCache;
    //         nextCache->prevCache = prevCache;
    //     }
    //     else if(prevCache != NULL){
    //         prevCache->nextCache = NULL;
    //     }
    //     else if(nextCache != NULL){
    //         nextCache->prevCache = NULL;
    //         computer->topCache = nextCache;
    //     } //     else{
    //         computer->topCache = NULL;
    //     }
    //     int _index = _ui.tabWidget_memory->currentIndex();
    //     _ui.tabWidget_memory->removeTab(_index);
    //     delete cache;
    //     delete cacheView;
    //
    //     int index = 1;
    //     //reset name
    //     for(Cache* curr = computer->topCache; curr != NULL; curr = curr->nextCache){
    //         _ui.tabWidget_memory->setTabText(_ui.tabWidget_memory->indexOf(curr->view),(new QString("Cache %1(BOTH)"))->arg(index++));
    //     }
    // }
    // else{
    //     printlnConsole("No cache to remove");
/*     } */
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
    qDebug() << "Build button is clicked";
    //Nothing to build
    //TODO output?
    int index = _ui.editorTab->currentIndex();
    if(index == -1){ 
        _ui.consoleTextEdit->appendPlainText("Nothing to build...");
        return;
    }
    //Save file: I don't know but eclipse does this, so I guess there is some reason why we need to save file before assembly
    _ui.editorTab->currentEditor()->clearMarks();
   assemble(_ui.editorTab->currentEditor()->sourceFile->fileName(), false); 
}

void MainWindow::assemble(QString fileName, bool runAfter){
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

    QMultiMap<QString, Problem> problemMap;

    for(int i =0; i < problemLog->size(); i++){
        Problem problem = problemLog->at(i);

        problemMap.insert(problem.fileName, problem);
        QString type = (problem.type == WARNING ? "Warning" :(problem.type == ERROR ? "Error" : "???"));
        _ui.problemTable->setItem(i,0,new QTableWidgetItem(type));
        _ui.problemTable->setItem(i,1,new QTableWidgetItem(problem.fileName));
        _ui.problemTable->setItem(i,2,new QTableWidgetItem(QString::number(problem.lineNumber+1)));
        _ui.problemTable->setItem(i,3,new QTableWidgetItem(QString::number(problem.wordNumber+1)));
        _ui.problemTable->setItem(i,4,new QTableWidgetItem(problem.cause));
    }

    for(QString fileName : problemMap.keys()){
        struct {
            bool operator()(Problem a, Problem b)
            {   
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
void MainWindow::handleBuildAll(){
    qDebug() << "Build All button is clicked";
    _ui.editorTab->currentEditor()->clearMarks();

}

void MainWindow::handlePreference(){
    qDebug() << "Preference button is clicked";
    PreferenceDialog dialog(this);
    dialog.exec();

    updateNavigation();
}

void MainWindow::handleForward(){
}
void MainWindow::handleBackward(){
}
void MainWindow::handleUpload(){
    qDebug() << "Upload button is clicked";
    //Nothing to build
    //TODO output?
    if(_ui.editorTab->isEmpty()){ 
        printlnConsole("Nothing to build...");
        return;
    }
    _ui.editorTab->currentEditor()->clearMarks();
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
    QList<uint> instructions = ProgramManagerX::loadProgram(fileName);
    //TODO fix this
    QList<QVariant> _instructions;

    //change this code
    _ui.tracker->clear();
    for(int i = 0; i < instructions.size(); i++){
        QString address = QString::number(INSTRUCTION_SIZE  * i,16).rightJustified(8, '0');
        QString instruction =disassembler->disassemble(instructions.at(i)); 
        QListWidgetItem *newItem = new QListWidgetItem; 
        newItem->setText(address + "\t" + instruction);
        QVariant bp (BreakPoint::NONE);
        newItem->setData(Qt::UserRole, BreakPoint::NONE);
        _ui.tracker->addItem(newItem);
        if(i == instructions.size()-1){
            newItem->setData(Qt::UserRole, BreakPoint::BREAK_ALL);
            newItem->setBackground(Qt::red);
        }
        _instructions.append(instructions.at(i));
    }
    sendMessage(ThreadMessage(ThreadMessage::R_LOAD,_instructions));
    _ui.tab_memory->update();
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
void MainWindow::updateUndo(bool avail) { _ui.actionUndo->setEnabled(avail); }

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
void MainWindow::handleCustomContextMenuForTracker(QPoint point){
    QPoint globalPos = _ui.tracker->mapToGlobal(point);

    QListWidgetItem* item = _ui.tracker->currentItem();
    if(item == NULL){
        return;
    }

    QMenu menu;
    QAction *addBreakAction = new QAction("Break once");
    addBreakAction->setEnabled(item->data(Qt::UserRole) != BreakPoint::BREAK);
    connect(addBreakAction,SIGNAL(triggered()), this, SLOT(handleAddBreak()));
    menu.addAction(addBreakAction);

    QAction *addBreakAllAction = new QAction("Break all");
    addBreakAllAction->setEnabled(item->data(Qt::UserRole) != BreakPoint::BREAK_ALL);
    connect(addBreakAllAction,SIGNAL(triggered()), this, SLOT(handleAddBreakAll()));
    menu.addAction(addBreakAllAction);

    QAction *addSkipAction = new QAction("Skip");
    addSkipAction->setEnabled(item->data(Qt::UserRole) != BreakPoint::SKIP);
    connect(addSkipAction,SIGNAL(triggered()), this, SLOT(handleAddSkip()));
    menu.addAction(addSkipAction);

    QAction *addSkipAllAction = new QAction("Skip all");
    addSkipAllAction->setEnabled(item->data(Qt::UserRole) != BreakPoint::SKIP_ALL);
    connect(addSkipAllAction,SIGNAL(triggered()), this, SLOT(handleAddSkipAll()));
    menu.addAction(addSkipAllAction);

    QAction *removeBreakAction = new QAction("No break");
    removeBreakAction->setEnabled(item->data(Qt::UserRole) != BreakPoint::NONE);
    connect(removeBreakAction,SIGNAL(triggered()), this, SLOT(handleRemoveBreak()));
    menu.addAction(removeBreakAction);

    QAction* action = menu.exec(globalPos);
}
void MainWindow::handleAddBreak(){
    QListWidgetItem* item = _ui.tracker->selectedItems().first();
    if(item == NULL){
        return;
    }
    item->setBackground(Qt::red);
    item->setData(Qt::UserRole, BreakPoint::BREAK);
}
void MainWindow::handleAddBreakAll(){
    QListWidgetItem* item = _ui.tracker->selectedItems().first();
    if(item == NULL){
        return;
    }
    item->setBackground(Qt::red);
    item->setData(Qt::UserRole, BreakPoint::BREAK_ALL);
}

void MainWindow::handleAddSkip(){
    QListWidgetItem* item = _ui.tracker->selectedItems().first();
    if(item == NULL){
        return;
    }
    item->setBackground(Qt::cyan);
    item->setData(Qt::UserRole, BreakPoint::SKIP);
}
void MainWindow::handleAddSkipAll(){
    QListWidgetItem* item = _ui.tracker->selectedItems().first();
    if(item == NULL){
        return;
    }
    item->setBackground(Qt::cyan);
    item->setData(Qt::UserRole, BreakPoint::SKIP_ALL);
}
void MainWindow::handleRemoveBreak(){
    QListWidgetItem* item = _ui.tracker->selectedItems().first();
    if(item == NULL){
        return;
    }
    item->setBackground(Qt::BrushStyle::NoBrush);
    item->setData(Qt::UserRole, BreakPoint::NONE);
}


void MainWindow::handlePlay(){
}

void MainWindow::procMessage(ThreadMessage message){
    qDebug() << "GUI:RECV FROM COMPUTER";
    ThreadMessage::Type type = message.type;
    QVariant info = message.message;
    switch(message.type){
        case ThreadMessage::A_OKAY:
            //Do nothing
            break;
        case ThreadMessage::A_ERROR:
            //Show error message
            break;
        case ThreadMessage::A_VIEW_MEMORY:
            _ui.tab_memory->display(info.toList());
            break;
        case ThreadMessage::A_VIEW_REGISTER:
            _ui.tab_register->display(info.toList());
            break;
        defualt:
            break;
    }
    messageQueue.dequeue();
    if(messageQueue.isEmpty() == false){
        emit _sendMessage(messageQueue.head());
    }

}
void MainWindow::sendMessage(ThreadMessage message){
    qDebug() << "GUI:SEND TO COMPUTER";
    //If queue is empty, send right away
    if(messageQueue.isEmpty()){
        messageQueue.enqueue(message);
        emit _sendMessage(message);
    }
    else{
        messageQueue.enqueue(message);
    }
}
