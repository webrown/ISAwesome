#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <iostream>
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
#include "ui_pisa.h"
#include "codeeditor.h"
#include "../Computer.h"
#include "../assembler/Assembler.h"
#include "newfiledialog.h"
#include "newcachedialog.h"
#include "PreferenceDialog.h"
#include "cacheview.h"
#include "../assembler/Disassembler.h"
#include <QThread>

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


    public slots:
        //Handlers
        void handleNewButton();
        void handleOpenButton();
        void handleUndoButton();
        void handleRedoButton();
        void handleSaveButton();
        void handleSaveAsButton();
        void handleAboutPISAButton();
        void handleAddCache();
        void handleRemoveCache();
        void handleClearCache();
        void handleFlushCache();
        void handleFlushAllCache();
        void handlePreference();
        void handleAssemblerConfiguration();
        void handleBuild();
        void handleBuildAll();

        void handleCloseTab(int index);
        void updateUndo(bool avail);
        void updateRedo(bool avail);
        void editorModified();
        void finishBuild(Assembled* assembled);
signals:
        void startBuild(QString fileName, AssemblerConfiguration config);

    private:
        QThread assemblyThread;
        Ui::MainWindow _ui;
        QSpinBox* createToolBarSpinBox();
        void createEditorTab(QString fileName);
};

#endif
