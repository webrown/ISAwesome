#ifndef MAINWINDOW_H
#define MAINWINDOW_H
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
#include "ui_pisa.h"
#include "CodeEditor.h"
#include "../Computer.h"
#include "MiscDialog.h"
#include "PreferenceDialog.h"
#include "CacheView.h"
#include "../assembler/Assembler.h"
#include "../assembler/Disassembler.h"
#include "../assembler/ProgramManagerX.h"
#include "HexSpinBox.h"

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

        void updateNavigation();

        void printConsole(QString line);
        void printlnConsole(QString line);
        void clearConsole();

        void displayProblems(QList<Problem>* problemLog);

        void launchProgram(QString fileName);

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
        void handleFlushCache();
        void handleFlushAllCache();
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
        void handleRemoveBreak();
        void handleUpload();


        void updateUndo(bool avail);
        void updateRedo(bool avail);
        void finishAssemble(Assembled* assembled, bool runAfter);
signals:
        void startBuild(QString fileName, AssemblerConfiguration config, bool runAfter);

    private:
        QThread assemblyThread;
        Ui::MainWindow _ui;
        void createEditorTab(QString fileName);
};

#endif
