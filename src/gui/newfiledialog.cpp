#include "newfiledialog.h"
#include <QStandardPaths>
#include <QFileDialog>
#include <cstdlib>
#include <string>

NewFileDialog::NewFileDialog(QString dir, QWidget *parent )
    : QDialog( parent )
{
    _ui.setupUi( this );
    connect(_ui.openButton, SIGNAL(clicked()), this, SLOT(handleOpenButton()));
    connect(_ui.randomButton, SIGNAL(clicked()), this,SLOT(handleRandomButton()));
    QString docLoc =  dir;
    _ui.lineEdit_directory->insert(docLoc); 
}


void NewFileDialog::handleOpenButton()
{
    QString dirName = QFileDialog::getExistingDirectory(
            this,
            "Open Files",
            _ui.lineEdit_directory->text()
            );
    if(!dirName.isEmpty()){
        _ui.lineEdit_directory->setText(dirName);
    }
}

void NewFileDialog::handleRandomButton()
{
    //QString name = "file" + rand();
    _ui.lineEdit_fileName->setText("file"+QString::number(rand()));
}

NewFileDialog::~NewFileDialog(){
    //nothing
}

QString NewFileDialog::getFileName(){
    QString fullName = _ui.lineEdit_directory->text() + _ui.lineEdit_fileName->text();
    QFile file(fullName);
    if(file.exists()){
        return "";
    }
    else{
        return fullName;
    }
}

