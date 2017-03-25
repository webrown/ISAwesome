#include "RegisterView.h"
#include "MainWindow.h"

RegisterView::RegisterView(QWidget *parent) : QTableWidget(parent){
    //Do nothing
}
RegisterView::~RegisterView(){
    //Do nothing
}
void RegisterView::init(MainWindow* main, QTableWidget* regTable, QComboBox* comboBox){
    this->main = main;
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
    qDebug() << "RegisterView: Update with ComboBox";
    QString line = comboBox->currentText();
    main->sendMessage(ThreadMessage(ThreadMessage::R_VIEW_REGISTER, line));
}

void RegisterView::display(QList<QVariant> list){
    QString line = list[0].toString();
    if(line == "General Registers"){
        line = "R";
    }
    else if(line.startsWith("Integer Vector #")){
        int num = line.remove("Integer Vector #").toInt();
        line = "R" + QString::number(num+24) + "_";
    }
    else if(line.startsWith("Float Vector #")){
        int num = line.remove("Float Vector #").toInt();
        line = "R" + QString::number(num+28) + "_";
    }
    else if(line == "Flag Registers"){
        line = "FLAG #";
    }
    for(int row =0; row< 64; row++){

        uint content = list[row+1].toUInt();
        regTable->item(row, 0)->setText(line+ QString::number(row).toUpper());
        regTable->item(row, 1)->setText("0X" + QString::number(content,16));
        regTable->item(row, 2)->setText(QString::number(content,10));
        regTable->item(row, 3)->setText("0B" + QString::number(content,2));
    }
}

