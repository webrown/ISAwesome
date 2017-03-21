#include "PreferenceDialog.h"
#include <QFileDialog>

PreferenceDialog::PreferenceDialog(QWidget *parent){
    _ui.setupUi( this );
    mainWindow = (MainWindow*) parent;

    _ui.lineEdit_WorkDirectory->setText( mainWindow->settings.value("general/workdirectory",getDocDir()).toString());
   
    _ui.globalAliasCheckBox->setChecked(mainWindow->settings.value("assembly/useGlobalAlias", true).toBool()); 
    _ui.defaultAliasCheckBox->setChecked(mainWindow->settings.value("assembly/useDefaultAlias", true).toBool()); 
    _ui.globalMacroCheckBox->setChecked(mainWindow->settings.value("assembly/useGlobalMacro", true).toBool()); 
    _ui.defaultMacroCheckBox->setChecked(mainWindow->settings.value("assembly/useDefaultMacro", true).toBool()); 
    _ui.wallCheckBox->setChecked(mainWindow->settings.value("assembly/useWall", true).toBool()); 
    _ui.mainEntryCheckBox->setChecked(mainWindow->settings.value("assembly/useMainEntry", true).toBool()); 

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

    mainWindow->settings.setValue("assembly/useGlobalAlias", _ui.globalAliasCheckBox->isChecked());
    mainWindow->settings.setValue("assembly/useDefaultAlias", _ui.defaultAliasCheckBox->isChecked());
    mainWindow->settings.setValue("assembly/useGlobalMacro", _ui.globalMacroCheckBox->isChecked());
    mainWindow->settings.setValue("assembly/useDefaultMacro", _ui.defaultMacroCheckBox->isChecked());
    mainWindow->settings.setValue("assembly/useWall", _ui.wallCheckBox->isChecked());
    mainWindow->settings.setValue("assembly/useMainEntry", _ui.mainEntryCheckBox->isChecked());

    QDialog::accept();
}
