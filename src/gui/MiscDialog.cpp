#include "MiscDialog.h"
NewCacheDialog::NewCacheDialog(MemoryStructure* container,  QWidget *parent )
    : QDialog( parent )
{
    this->container = container;
    _ui.setupUi( this );

    MemoryInterface* instM = container->_instructionAccess;
    MemoryInterface* dataM = container->_dataAccess;
    int level = 1;
    while(dataM->type != Cache::BOTH || instM->type != Cache::BOTH){
        if(instM->type != Cache::BOTH){
            _ui.nextBox->addItem("Level " + QString::number(level) + " Cache(I)", {instM->id});
            qDebug() << "INST " << instM->id << "->" <<instM->next->id;
            instM = instM->next;
        }
        if(dataM->type != Cache::BOTH){
            _ui.nextBox->addItem("Level " + QString::number(level) + " Cache(D)", {dataM->id});
            qDebug() << "DATA " << dataM->id << "->" << dataM->next->id;
            dataM = dataM->next;

        }
        level++;
    }
    for(; instM != NULL; instM = instM->next){
        _ui.nextBox->addItem("Level " + QString::number(level) + " Cache(I&D)", {instM->id});
        QString something = (instM->id ==0) ? "" : QString::number(instM->next->id);
            qDebug() << "BOTH " <<instM->id << "->" << something;

        level++;
    }

    _ui.nextBox->setItemText(_ui.nextBox->count()-1, "Main Memory");

}

NewCacheDialog::~NewCacheDialog(){
    //Do nothing
}

void NewCacheDialog::accept(){
    //If size is zero, then only main memory exists, so no error
    qDebug() << _ui.nextBox->currentText();
    qDebug() << _ui.nextBox->currentData();
    if(container->addCache(_ui.nextBox->currentData().toInt(), getType(), getIndex(), getOffset(), getWay(), getDelay()) == false){
        qDebug() << "GUI: Invalid Cache structure";
        return;
    }
    QDialog::accept();
}


Cache::Type NewCacheDialog::getType(){
    if(_ui.typeBox->currentText() == "Both"){
        return Cache::BOTH;
    }
    else if(_ui.typeBox->currentText() == "Data Only"){
        return Cache::DATA_ONLY;
    }
    else if(_ui.typeBox->currentText() == "Instruction Only"){
        return Cache::INSTRUCTION_ONLY;
    }
    else{
        qDebug() << "Oops -from new cache dialog";
        exit(-1);
    }
}

int NewCacheDialog::getIndex(){
    return _ui.indexSpin->value();
}

int NewCacheDialog::getOffset(){
    return _ui.offsetSpin->value();
}
int NewCacheDialog::getWay(){
    return _ui.waySpin->value();
}
double NewCacheDialog::getDelay(){
    return _ui.delaySpin->value();
} 





//----------------------------------------------------
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

