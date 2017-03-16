#include "PreferenceDialog.h"
#include <QFileDialog>

PreferenceDialog::PreferenceDialog(QWidget *parent){
    _ui.setupUi( this );
    mainWindow = (MainWindow*) parent;

    _ui.lineEdit_WorkDirectory->setText( mainWindow->settings.value("general/workdirectory",getDocDir()).toString());
}
PreferenceDialog::~PreferenceDialog(){
}
void PreferenceDialog::handleOpen_WorkDirectory(){

    QString workDirectory = QFileDialog::getExistingDirectory(
            this,
            "Open Files",
            mainWindow->settings.value("general/workdirectory",getDocDir()).toString()
            ,
            QFileDialog::ShowDirsOnly);
    _ui.lineEdit_WorkDirectory->setText(workDirectory);
}
void PreferenceDialog::accept(){
    mainWindow->settings.setValue("general/workdirectory", _ui.lineEdit_WorkDirectory->text());
    QDialog::accept();
}
