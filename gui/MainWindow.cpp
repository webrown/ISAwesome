#include <stdio.h>
#include <QFrame>
#include "MainWindow.h"


MainWindow::MainWindow( QWidget *parent )
	: QMainWindow( parent )
{
	_ui.setupUi( this );
	_ui.toolBar->insertWidget(_ui.actionforward,createToolBarSpinBox());

	connect(_ui.actionnew, SIGNAL(triggered()), this, SLOT (handleButton()));

	//testcode
	_ui.tabWidget_editor->addTab(createEditorTab(), "new file");
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


//handle toolbar button clicked event
void MainWindow::handleButton()
{
	printf("%s\n", "clicked");
}

//add page on editor
QPlainTextEdit* MainWindow::createEditorTab()
{
	QPlainTextEdit* widget = new QPlainTextEdit();
	widget->setFrameStyle(QFrame::NoFrame);
	return widget;
	

}


