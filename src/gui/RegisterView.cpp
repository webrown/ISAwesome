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

    regTable->setRowCount(65); for(int row = 0; row < 65; row++){
        for(int col =0; col < 20; col++){
            regTable->setItem(row, col, new QTableWidgetItem());
        }
    }
    for(int i = 4; i < 20; i++){
        regTable->setColumnWidth(i, 37);
    }
    connect(comboBox, SIGNAL (activated(int)), this, SLOT(updateWithComboBox()));
    connect(regTable->horizontalHeader(),SIGNAL(sectionDoubleClicked(int)),this,SLOT(handleHeader(int)));

    update();
    //Yeah, why not?
    regTable->horizontalHeaderItem(2)->setText("Decimal");


}
void RegisterView::handleHeader(int x){
    if(x == 2){
        mode = static_cast<Mode>((mode +1) %3);
        update();
    }
    switch(mode){
        case DEC:
        regTable->horizontalHeaderItem(2)->setText("Decimal");
        break;
        case FLOAT:
        regTable->horizontalHeaderItem(2)->setText("Float");
        break;
        case INT:
        regTable->horizontalHeaderItem(2)->setText("Integer");
        break;
    };
}

void RegisterView::update(){
    updateWithComboBox(); }

void RegisterView::updateWithComboBox(){
    qDebug() << "GUI: Update with ComboBox";
    QString line = comboBox->currentText();
    main->sendMessage(ThreadMessage(ThreadMessage::R_VIEW_REGISTER, line));
}

void RegisterView::display(QList<QVariant> list){
    QString line = list[0].toString();
    //display something that is flag
    if(line == "Flag Registers"){
        regTable->setRowHidden(64, false);
        regTable->setColumnHidden(1,true);
        regTable->setColumnHidden(2,true);
        regTable->setColumnHidden(3,true);

        regTable->setColumnHidden(4,false);
        regTable->setColumnHidden(5,false);
        regTable->setColumnHidden(6,false);
        regTable->setColumnHidden(7,false);
        regTable->setColumnHidden(8,false);
        regTable->setColumnHidden(9,false);
        regTable->setColumnHidden(10,false);
        regTable->setColumnHidden(11,false);
        regTable->setColumnHidden(12,false);
        regTable->setColumnHidden(13,false);
        regTable->setColumnHidden(14,false);
        regTable->setColumnHidden(15,false);
        regTable->setColumnHidden(16,false);
        regTable->setColumnHidden(17,false);
        regTable->setColumnHidden(18,false);
        regTable->setColumnHidden(19,false);

        line = "FLAG #";
        regTable->item(0, 0)->setText("The Flag");
        color(0, list[1].toUInt());

        for(int row = 0; row < 64; row++){
            uint content = list[row+2].toUInt();
            regTable->item(row+1, 0)->setText(line + QString::number(row));
            color(row+1, content);
        }
        return;

    }
    //display something that is not flag
    regTable->setRowHidden(64, true);
    regTable->setColumnHidden(2,false);
    regTable->setColumnHidden(3,false);

    regTable->setColumnHidden(4,true);
    regTable->setColumnHidden(5,true);
    regTable->setColumnHidden(6,true);
    regTable->setColumnHidden(7,true);
    regTable->setColumnHidden(8,true);
    regTable->setColumnHidden(9,true);
    regTable->setColumnHidden(10,true);
    regTable->setColumnHidden(11,true);
    regTable->setColumnHidden(12,true);
    regTable->setColumnHidden(13,true);
    regTable->setColumnHidden(14,true);
    regTable->setColumnHidden(15,true);
    regTable->setColumnHidden(16,true);
    regTable->setColumnHidden(17,true);
    regTable->setColumnHidden(18,true);
    regTable->setColumnHidden(19,true);


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
    for(int row =0; row< 64; row++){
        uint content = list[row+1].toUInt();
        if(line == "R" && row >= 24){
            regTable->item(row, 0)->setText("");
            regTable->item(row, 1)->setText("");
            regTable->item(row, 2)->setText("");
            regTable->item(row, 3)->setText("");
        }
        else{
            regTable->item(row, 0)->setText(line+ QString::number(row).toUpper());
            regTable->item(row, 1)->setText("0X" + QString::number(content,16).rightJustified(8, '0'));
            switch(mode){
                case FLOAT:
                    {
                    // qDebug() << list[row+1];
                    int v = list[row+1].toUInt();
                    float * vv= (float *) & v;
                    regTable->item(row, 2)->setText(QString::number(*vv));
                    break;
                    }
                case INT:
                    {
                    int v = list[row+1].toUInt();
                    regTable->item(row, 2)->setText(QString::number(v));
                    break;
                    }
                case DEC:
                    regTable->item(row, 2)->setText(QString::number(list[row+1].toUInt()));
                    break;
            };
            regTable->item(row, 3)->setText("0B" + QString::number(content,2).rightJustified(32,'0'));
        }
    }
}
void RegisterView::color(int row, uint v){
    int x = 1;
    for(int i =0; i < 16 ;i++){

        int flag = v & x;
        if(flag != 0)
            regTable->item(row, i + 4)->setBackground(Qt::red);
        else
            regTable->item(row, i + 4)->setBackground(Qt::white);
        x = x << 1;
    }
}

