#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSpinBox>
#include <QWidget>
#include <QPlainTextEdit>
#include "ui_pisa.h"
class MainWindow : public QMainWindow
{
	Q_OBJECT
	public:
		explicit MainWindow( QWidget *parent = 0);
		~MainWindow();

	public slots:
		void handleButton();

	private:
		Ui::MainWindow _ui;
		QSpinBox* createToolBarSpinBox();
		QPlainTextEdit* createEditorTab();
};

#endif
