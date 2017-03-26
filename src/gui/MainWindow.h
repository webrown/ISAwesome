#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "MemoryView.h"
#include <iostream>
#include <typeinfo>
#include <QFileDialog>
#include <QMetaType>
#include <QInputDialog>
#include <QStandardPaths>
#include <QTextStream>
#include <QDialog>
#include <QLabel>
#include <QDesktopServices>
#include <QDebug>
#include <QMainWindow>
#include <QSpinBox>
#include <QWidget>
#include <QPlainTextEdit>
#include <QFileSystemModel>
#include <QSettings>
#include <QThread>
#include <QFileInfo>
#include <QMessageBox>
#include "ui_pisa.h"
#include "CodeEditor.h"
#include "../computer/Computer.h"
#include "MiscDialog.h"
#include "PreferenceDialog.h"
#include "CacheView.h"
#include "../assembler/Assembler.h"
#include "../assembler/Disassembler.h"
#include "../assembler/ProgramManagerX.h"
#include "HexSpinBox.h"
#include "../computer/BreakPoint.h"
#include "CacheModel.h"
Q_DECLARE_METATYPE(ThreadMessage);
Q_DECLARE_METATYPE(CacheModel);

class MainWindow : public QMainWindow
{
    Q_OBJECT
    public:
        explicit MainWindow( QWidget *parent = 0);
        ~MainWindow();
        Computer* computer;
        Assembler* assembler;
        Disassembler* disassembler;
        QSettings settings;

        QQueue<ThreadMessage> messageQueue;

        QList<CacheModel> cacheModels;

        QSpinBox* cycleSpinBox;
        HexSpinBox* pcSpinBox; 

        //@@@TODO FIX THIS SOON
        QListWidgetItem* currItem = NULL;
        //@@@
        void updateNavigation();

        void printConsole(QString line);
        void printlnConsole(QString line);
        void clearConsole();

        void displayProblems(QList<Problem>* problemLog);

        void uploadProgram(QString fileName);

        bool shouldIAssemble(); 
        void assemble(QString fileName, bool runAfter);

    public slots:
            //Handlers
        void handleNew();
        void handleOpen();
        void handleUndo();
        void handleRedo();
        void handleSave();
        void handleSaveAs();
        void handleSaveAll();
        void handleAboutPISA();
        void handleAddCache();
        void handleRemoveCache();
        void handleClearCache();
        void handlePreference();
        void handleBuild();
        void handleBuildAll();
        void handleForward();
        void handleBackward();
        void handlePlay();
        void handlePause();
        void handleStop();
        void handleOpenFromNavigation(QModelIndex index);
        void handleCustomContextMenuForTracker(QPoint point);
        void handleAddBreak();
        void handleAddBreakAll();
        void handleAddSkip();
        void handleAddSkipAll();
        void handleRemoveBreak();
        void handleUpload();
        void handleErrorFromComputer(QString errorMessage);
        void handleUpdatePC(int);

        void update(uint pc);
        void updateByState(Computer::State state);
        void updateMemoryWidget();

        void updateUndo(bool avail);
        void updateRedo(bool avail);
        void finishAssemble(Assembled* assembled, bool runAfter);
        void procMessage(ThreadMessage message);
        void sendMessage(ThreadMessage message);
    signals:
        void startBuild(QString fileName, AssemblerConfiguration config, bool runAfter);
        void _sendMessage(ThreadMessage message);

    private:
        QThread* computerThread;
        QThread* assemblyThread;
        Ui::MainWindow _ui;
};

#endif
