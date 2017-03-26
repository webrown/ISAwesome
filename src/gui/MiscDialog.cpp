#include "MiscDialog.h"
NewCacheDialog::NewCacheDialog(QList<CacheModel>* cacheModels,  QWidget *parent )
    : QDialog( parent )
{
    this->cacheModels = cacheModels;
    _ui.setupUi( this );

    


    int index = 0;
   for(CacheModel  curr : *cacheModels){ 
       QString line = "Cache #" + curr.level;
        if(curr.type == Cache::DATA_ONLY){
            line += " (Data Only)";
        }
        else if(curr.type == Cache::INSTRUCTION_ONLY){
            line += " (Instruction Only)";
        }
        else if(curr.type == Cache::BOTH){
            line += " (Both)";
        }
        _ui.nextBox->addItem(line, {index++});
   } 
    _ui.nextBox->addItem("Main Memory");

    _ui.nextBox->setCurrentIndex(0);
}

NewCacheDialog::~NewCacheDialog(){
    //Do nothing
}

void NewCacheDialog::accept(){
    //If size is zero, then only main memory exists, so no error
    if(cacheModels->size() == 0){
        QDialog::accept();
        return;
    }
    CacheModel next =  cacheModels->at(_ui.nextBox->currentData().toInt());
    if(next.type != Cache::BOTH && _ui.typeBox->currentText() == "Both"){
        //Invalid selection
        return;
    }
    
    QDialog::accept();
}

CacheModel NewCacheDialog::getModel(){
    CacheModel model;
    if(_ui.typeBox->currentText() == "Both"){
        model.type = Cache::BOTH;
    }
    else if(_ui.typeBox->currentText() == "Data Only"){
        model.type = Cache::DATA_ONLY;
    }
    else if(_ui.typeBox->currentText() == "Instruction Only"){
        model.type = Cache::INSTRUCTION_ONLY;
    }
    else{
        qDebug() << "Oops -from cache new dialog";
        exit(-1);
    }
    if(cacheModels->size() == 0){
        model.level = 1;
        cacheModels->append(model);
    }
    else{
        int index =_ui.nextBox->currentData().toInt( );
        while(index > 0 && cacheModels->at(index-1).level == cacheModels->at(index).level){
            index--;
        }
        model.level = cacheModels->at(index).level;
        for(int i = index+1; i < cacheModels->size();i++){
            // cacheModels->at(i).level =cacheModels->at(i).level + 1;
        }
        cacheModels->insert(index, model) ;
        

    }
    model.indexBits = _ui.indexSpin->value();
    model.logDataWordCount = _ui.offsetSpin->value();
    model.logAssociativity = _ui.waySpin->value();
    model.delay = _ui.delaySpin->value();
    return model;
}
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
    QString fullPath = _ui.lineEdit_directory->text() + _ui.lineEdit_fileName->text();
    return fullPath;
}

void NewFileDialog::accept(){
    if(_ui.lineEdit_fileName->text() == ""){
       //  QErrorMessage msg(this); */
        // msg.showMessage("Empty string can't be a file name");
       // msg.exec();
        return;
    }
    QFile file(getFileName());
    if(file.exists() == true){
        QMessageBox msgBox;
        msgBox.setText(getFileName() + " already exists.");
        msgBox.setInformativeText("Do you want to proceed?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();
        if(ret == QMessageBox::Yes){
            QDialog::accept();
        }
        else if (ret == QMessageBox::No){
            //Nothing
        }
        else if (ret == QMessageBox::Cancel){
            QDialog::reject();
        }
            
    }
    else{
        QDialog::accept();
    }
}

