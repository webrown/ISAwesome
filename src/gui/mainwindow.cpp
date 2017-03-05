#include <iostream>
#include <QFileDialog>
#include <QInputDialog>
#include <QStandardPaths>
#include <QTextStream>
#include <QDialog>
#include "mainwindow.h"
#include "newfiledialog.h"
#include "newcachedialog.h"
#include "cacheview.h"
#include <QLabel>
#include <QDesktopServices>
#include <QDebug>

MainWindow::MainWindow( QWidget *parent )
    : QMainWindow( parent )
{
    _ui.setupUi( this );

    //add element on toolbar
    _ui.toolBar->insertWidget(_ui.actionforward,createToolBarSpinBox());

    QLabel* pcLabel = new QLabel("PC: F20A3E0A");
    _ui.toolBar->addWidget(pcLabel);

    //connect input widget to event handler
    connect(_ui.actionnew, SIGNAL(triggered()), this, SLOT (handleNewButton()));
    connect(_ui.actionNew, SIGNAL(triggered()), this, SLOT (handleNewButton()));
    connect(_ui.actionopen, SIGNAL(triggered()), this, SLOT (handleOpenButton())); connect(_ui.actionOpen, SIGNAL(triggered()), this, SLOT (handleOpenButton()));
    connect(_ui.actionSave, SIGNAL(triggered()), this, SLOT (handleSaveButton()));
    connect(_ui.actionsave, SIGNAL(triggered()), this, SLOT (handleSaveButton()));
    connect(_ui.actionUndo, SIGNAL(triggered()), this, SLOT (handleUndoButton()));
    connect(_ui.actionRedo, SIGNAL(triggered()), this, SLOT (handleRedoButton()));
    connect(_ui.actionSave_As, SIGNAL(triggered()), this, SLOT (handleSaveAsButton()));
    connect(_ui.actionAbout_PISA, SIGNAL(triggered()), this, SLOT (handleAboutPISAButton()));
    
    connect(_ui.actionAddCache, SIGNAL(triggered()), this, SLOT (handleAddCache()));
    connect(_ui.actionRemoveCache, SIGNAL(triggered()), this, SLOT (handleRemoveCache()));
    connect(_ui.actionClearCache, SIGNAL(triggered()), this, SLOT (handleClearCache()));
    connect(_ui.actionFlushCache, SIGNAL(triggered()), this, SLOT (handleFlushCache()));
    connect(_ui.acitonFlushAllCache, SIGNAL(triggered()), this, SLOT (handleFlushAllCache()));


    //connect close tab stuff for editor tabs
    connect(_ui.tabWidget_editor, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));

    //disable both undo and redo
    _ui.actionUndo->setEnabled(false);
    _ui.actionRedo->setEnabled(false);
    QTableWidgetItem *newItem = new QTableWidgetItem("Hello");
    _ui.tableWidget_memory->setRowCount(1000);
    _ui.tableWidget_memory->setItem(0,0,newItem);
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
    //delete _ui;
}

//handle New Event
void MainWindow::handleNewButton(){
    NewFileDialog dialog(this);
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
    QString docLoc = QStandardPaths::locate(QStandardPaths::DocumentsLocation, QString(), QStandardPaths::LocateDirectory);
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
    NewFileDialog dialog(this);
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
void MainWindow::closeTab(int index){
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

