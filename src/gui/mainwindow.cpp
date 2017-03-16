#include "mainwindow.h"
MainWindow::MainWindow( QWidget *parent ): QMainWindow( parent ),settings("CS535","PISA")
{
    _ui.setupUi( this );

    //Don't ask me what these lines do... 
    qRegisterMetaType<AssemblerConfiguration>();
    qRegisterMetaType<Assembled>();

    //move assembly to different thread
    assembler = new Assembler();
    disassembler = new Disassembler();
    computer = new Computer();
    assembler->moveToThread(&assemblyThread);
    connect(&assemblyThread, &QThread::finished, assembler, &QObject::deleteLater);
    connect(this, &MainWindow::startBuild, assembler, &Assembler::assemble);
    connect(assembler, &Assembler::resultReady, this, &MainWindow::finishBuild);
    assemblyThread.start();

    //add element on toolbar
    _ui.toolBar->insertWidget(_ui.actionforward,createToolBarSpinBox());

    QLabel* pcLabel = new QLabel("PC: F20A3E0A");
    _ui.toolBar->addWidget(pcLabel);

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

}

QSpinBox* MainWindow::createToolBarSpinBox()
{
    QSpinBox* spinbox = new QSpinBox();
    spinbox->setValue(1);
    spinbox->setRange(0,1000);
    return spinbox;
}
MainWindow::~MainWindow()
{
    delete computer;
    delete assembler;
    delete disassembler;
    qDebug() << "Close MainWindow";
    qDebug() << "2";
    assemblyThread.quit();
    assemblyThread.wait();
    qDebug() << "Fin.";
}


//handle New Event
void MainWindow::handleNewButton(){
    NewFileDialog dialog(settings.value("general/workdirectory",getDocDir()).toString(),this);
    int result = dialog.exec();
    if(result == QDialog::Accepted){
        QString str = dialog.getFileName();
        if(!str.isEmpty())
            createEditorTab(str);
    }
}

//handle Open Event
void MainWindow::handleOpenButton()
{
    QString docLoc = settings.value("general/workdirectory",getDocDir()).toString();
    QStringList fileNames = QFileDialog::getOpenFileNames(
            this,
            "Open Files",
            docLoc,
            "Any");
    for(QString fileName : fileNames){
        //check whether we already open the file
        bool isExist = false;
        for(int i =0; i < _ui.tabWidget_editor->count(); i++){
            if(((CodeEditor*) _ui.tabWidget_editor->widget(i))->file->fileName() == (fileName)){
                isExist = true;
                break;
            }
        }

        if(!isExist)
            createEditorTab(fileName);
    }
}

//handle Save event
void MainWindow::handleSaveButton()
{
    int index = _ui.tabWidget_editor->currentIndex();
    if(index == -1) 
        return;

    //update tab name
    QString title = _ui.tabWidget_editor->tabText(index);
    if(title.endsWith("*")){
        title.remove(title.length()-1,1);
    }
    _ui.tabWidget_editor->setTabText(index, title);

    //save file
    ((CodeEditor*)_ui.tabWidget_editor->widget(index))->write();

}

//handle Save As event
void MainWindow::handleSaveAsButton()
{
    NewFileDialog dialog(settings.value("general/workdirectory",getDocDir()).toString(),this);
    int result = dialog.exec();
    if(result == QDialog::Accepted){
        QString str = dialog.getFileName();
        if(!str.isEmpty())
             ((CodeEditor*)_ui.tabWidget_editor->currentWidget())->writeAs(str);

    }
}

//handle Undo Event
void MainWindow::handleUndoButton()
{
    ((CodeEditor*)_ui.tabWidget_editor->currentWidget())->undo();
}

void MainWindow::handleRedoButton()
{
    ((CodeEditor*)_ui.tabWidget_editor->currentWidget())->redo();

}

//hande about pisa event
void MainWindow::handleAboutPISAButton()
{
    QString link = "https://github.com/webrown/PISA";
    QDesktopServices::openUrl(QUrl(link));
}

//add page on editor
void MainWindow::createEditorTab(QString fileName)
{
    //create file
    QFile* file = new QFile(fileName); 
    CodeEditor* widget = new CodeEditor(file);

    //connect undo and redo button
    connect(widget, SIGNAL(undoAvailable(bool)), this, SLOT(updateUndo(bool)));
    connect(widget, SIGNAL(redoAvailable(bool)), this, SLOT(updateRedo(bool)));
    connect(widget, SIGNAL(textChanged()), this, SLOT(editorModified()));
    
    QString _fileName = fileName.section("/",-1,-1);   
    _ui.tabWidget_editor->addTab(widget, _fileName);  
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

//close tab
void MainWindow::handleCloseTab(int index){
    _ui.tabWidget_editor->removeTab(index);
}

//editor is modified, we need to put * next to title
void MainWindow::editorModified()
{
        int index = _ui.tabWidget_editor->currentIndex();
        QString title = _ui.tabWidget_editor->tabText(index);
        if(!title.endsWith("*")){
            title = title + "*";
        }
        _ui.tabWidget_editor->setTabText(index,title);
}

void MainWindow::handleAddCache(){ 
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
}

void MainWindow::handleClearCache(){
}

void MainWindow::handleFlushCache(){
}

void MainWindow::handleFlushAllCache(){
}
void MainWindow::handleBuild(){
    //Nothing to build
    //TODO output?
    int index = _ui.tabWidget_editor->currentIndex();
    if(index == -1){ 
        _ui.consoleTextEdit->appendPlainText("Nothing to build...");
        return;
    }
    handleSaveButton();

    AssemblerConfiguration config;
    config.useDefaultMacro = settings.value("assembly/useDefaultMacro", true).toBool();
    config.useDefaultAlias = settings.value("assembly/useDefaultAlias", true).toBool();
    config.useGlobalMacro = settings.value("assembly/useGlobalMacro", true).toBool();
    config.useGlobalAlias = settings.value("assembly/useGlobalAlias", true).toBool();
    config.useMainEntry = settings.value("assembly/useMainEntry", true).toBool();
   
    startBuild(((CodeEditor*)_ui.tabWidget_editor->currentWidget())->file->fileName(), config);
}

void MainWindow::finishBuild(Assembled* assembled){
    _ui.problemTable->clearContents();
    _ui.problemTable->setRowCount(0);
    _ui.tracker->clear();

   if(assembled->isAssembled){
       _ui.consoleTextEdit->appendPlainText("Build succeeded.");
       for(int i = 0; i < assembled->instructions->size(); i++){
           _ui.tracker->addItem(disassembler->disassemble(assembled->instructions->at(i)));
       }

       delete assembled->instructions;
   }
   else{
       _ui.consoleTextEdit->appendPlainText("Build failed...");
       _ui.problemTable->setRowCount(assembled->errorLog->size());
       for(int i =0; i < assembled->errorLog->size(); i++){
           qDebug() << "printing out error";
           Error error = assembled->errorLog->at(i);
           qDebug() << error.fileName;
           QTableWidgetItem *typeItem = new QTableWidgetItem("Error");
           _ui.problemTable->setItem(i,0,typeItem);
           QTableWidgetItem *fileItem = new QTableWidgetItem(error.fileName);
           _ui.problemTable->setItem(i,1,fileItem);
           QTableWidgetItem *lineItem = new QTableWidgetItem(QString::number(error.lineNumber+1));
           _ui.problemTable->setItem(i,2,lineItem);
           QTableWidgetItem *wordItem = new QTableWidgetItem(QString::number(error.wordNumber+1));
           _ui.problemTable->setItem(i,3,wordItem);
           QTableWidgetItem *causeItem = new QTableWidgetItem(error.cause);
           _ui.problemTable->setItem(i,4,causeItem);
       }
       delete assembled->errorLog;
   }

   _ui.consoleTextEdit->appendPlainText("Time elasped: " + QString::number(assembled->elaspedTime) + " msec");
    delete assembled->warningLog;
    delete assembled;

}
void MainWindow::handleBuildAll(){
}

void MainWindow::handlePreference(){
    PreferenceDialog dialog(this);
    dialog.exec();
}
void MainWindow::handleAssemblerConfiguration(){
}
