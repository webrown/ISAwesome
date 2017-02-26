#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSpinBox>
#include <QWidget>
#include <QPlainTextEdit>
#include "codeeditor.h"
#include "ui_pisa.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT
	public:
		explicit MainWindow( QWidget *parent = 0);
		~MainWindow();

	public slots:
		void handleNewButton();
		void handleOpenButton();
                void handleUndoButton();
                void handleRedoButton();
                void handleSaveButton();
                void handleSaveAsButton();
                void handleAboutPISAButton();
		void closeTab(int index);
                void updateUndo(bool avail);
                void updateRedo(bool avail);
                void editorModified();

	private:
		Ui::MainWindow _ui;
		QSpinBox* createToolBarSpinBox();
		void createEditorTab(QString fileName);
};

#endif
