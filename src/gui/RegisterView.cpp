#include "RegisterView.h"

RegisterView::RegisterView(){
    //Do nothing
}
RegisterView::~RegisterView(){
    //Do nothing
}
void RegisterView::init(Register* regs, QTableWidget* regTable, QComboBox* comboBox){
    this->regs = regs;
    this->regTable =regTable;
    this->comboBox = comboBox;

    regTable->setRowCount(64);
    for(int row = 0; row < 64; row++){
        regTable->setItem(row, 0, new QTableWidgetItem());
        regTable->setItem(row, 1, new QTableWidgetItem());
        regTable->setItem(row, 2, new QTableWidgetItem());
        regTable->setItem(row, 3, new QTableWidgetItem());
    }
    connect(comboBox, SIGNAL (activated(int)), this, SLOT(updateWithComboBox()));

    update();

}

void RegisterView::update(){
    updateWithComboBox();
}

void RegisterView::updateWithComboBox(){
    QString line = comboBox->currentText();
    if(line == "General Registers"){
        qDebug() << "Show General Registers";
        showGeneral();
    }
    else if(line.startsWith("Integer Vector #")){
        int num = line.remove("Integer Vector #").toInt();
        qDebug() << "Show Integer Vector#" <<QString::number(num);

        showVector(num);
    }
    else if(line.startsWith("Float Vector #")){
        int num = line.remove("Float Vector #").toInt();
        qDebug() << "Show Float Vector#" <<QString::number(num);
        showVector(num + 4);
    }
    else if(line == "Flag Registers"){
        qDebug() << "Show Flag Registers";
        showFlags();
    }
}

void RegisterView::showVector(int n){
    //Get correct vector
    QVector<Value> vec = n < 4 ? regs->_iVecs[n] : regs->_fVecs[n-4];
    QString num = QString::number(n +24);
    qDebug() << "X";
    for(int row =0; row< 64; row++){
        uint content = vec[row].asUInt;
        regTable->item(row, 0)->setText("R" + num + "_"+ QString::number(row).toUpper());
        regTable->item(row, 1)->setText("0X" + QString::number(content,16));
        regTable->item(row, 2)->setText(QString::number(content,10));
        regTable->item(row, 3)->setText("0B" + QString::number(content,2));
    }

}
void RegisterView::showGeneral(){
    int row =0;
    for(;row < 10; row++){
        uint content = regs->_iScas[row].asUInt;
        regTable->item(row, 0)->setText("R" + QString::number(row));
        regTable->item(row, 1)->setText("0X" + QString::number(content, 16).toUpper());
        regTable->item(row, 2)->setText(QString::number(content, 10));
        regTable->item(row, 3)->setText("0B" + QString::number(content, 2));
    }
    for(;row<20; row++){
        uint content = regs->_fScas[row-10].asUInt;
        regTable->item(row, 0)->setText("R" + QString::number(row));
        regTable->item(row, 1)->setText("0X" + QString::number(content, 16).toUpper());
        regTable->item(row, 2)->setText(QString::number(content, 10));
        regTable->item(row, 3)->setText("0B" + QString::number(content, 2));
    }

    for(;row<24;row++){
        uint content = regs->_sRegs[row-20].asUInt;
        regTable->item(row, 0)->setText("R" + QString::number(row));
        regTable->item(row, 1)->setText("0X" + QString::number(content, 16).toUpper());
        regTable->item(row, 2)->setText(QString::number(content, 10));
        regTable->item(row, 3)->setText("0B" + QString::number(content, 2));
 
    }

    for(;row<64;row++){
        regTable->item(row, 0)->setText("");
        regTable->item(row, 1)->setText("");
        regTable->item(row, 2)->setText("");
        regTable->item(row, 3)->setText("");
    }
}
void RegisterView::showFlags(){
    QVector<Value> vec = regs->_flagVec;
    for(int row =0; row< 64; row++){
        uint content = vec[row].asUInt;
        regTable->item(row, 0)->setText("FLAG #" + QString::number(row));
        regTable->item(row, 1)->setText("0X"+QString::number(content,16).toUpper());
        regTable->item(row, 2)->setText("" + QString::number(content,10));
        regTable->item(row, 3)->setText("0B" + QString::number(content,2));
    }
}
