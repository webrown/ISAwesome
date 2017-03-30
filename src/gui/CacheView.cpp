#include "CacheView.h"
#include "MainWindow.h"
#define NUMBER_OF_DEFAULT_HEADERS 5


CacheView::CacheView(QWidget * parent) : QTableWidget(parent){
}

CacheView::~CacheView(){
}

void CacheView::init(MainWindow* main, QTableWidget* memoryTable, QComboBox* comboBox, QPushButton* searchButton, QLineEdit* lineEdit, QLineEdit* indexEdit, QLineEdit* offsetEdit, QPushButton* nextButton, QPushButton* prevButton){
    this->main = main;
    this->table = memoryTable;
    this->comboBox = comboBox;
    this->searchButton =searchButton;
    this->tagEdit = lineEdit;
    this->indexEdit = indexEdit;
    this->offsetEdit = offsetEdit;
    this->nextButton = nextButton;
    this->prevButton = prevButton;

    table->setRowCount(64);
    for(int row = 0; row < 64; row++){
        table->setItem(row, 0, new QTableWidgetItem());
        table->setItem(row, 1, new QTableWidgetItem());
        table->setItem(row, 2, new QTableWidgetItem());
        table->setItem(row, 3, new QTableWidgetItem());
        table->setItem(row, 4, new QTableWidgetItem());
        table->setItem(row, 5, new QTableWidgetItem());
        table->setItem(row, 6, new QTableWidgetItem());
    }

    table->setColumnWidth(0,20);
    table->setColumnWidth(1,20);
    table->setColumnWidth(2,45);

    connect(comboBox, SIGNAL (activated(int)), this, SLOT(updateWithComboBox()));
    connect(searchButton, SIGNAL (clicked()), this, SLOT(updateWithSearch()));
    connect(nextButton, SIGNAL (clicked()), this, SLOT(handleNextButton()));
    connect(prevButton, SIGNAL (clicked()), this, SLOT(handlePrevButton()));

}




void CacheView::update(){
    updateWithComboBox();
}

void CacheView::display(QList<QVariant> list){
    qDebug() << count;
    int id = list.takeFirst().toInt();
    DummyMem* model = (DummyMem*) main->container.map[id];
    // qDebug() << list;
    // qDebug() << list.size();
    int i;
    table->setColumnHidden(2, model->logAssociativity==0);
    table->setColumnHidden(4, model->indexBits==0);
    table->setColumnHidden(5, model->logDataWordCount==0);
    
    int tagSize = 32-model->indexBits-model->logDataWordCount;
    int bitSize = fontMetrics().width('0') + 1;

    int tagWidth = qMax(bitSize * 3 + 15, tagSize * bitSize);
    int indexWidth = qMax(bitSize * 5 + 15, model->indexBits * bitSize);
    int offsetWidth = qMax(bitSize * 6 + 15, model->logDataWordCount * bitSize);
    
    table->setColumnWidth(3,tagWidth);
    table->setColumnWidth(4,indexWidth);
    table->setColumnWidth(5,offsetWidth);

    for(i = 0;i < list.size()/7; i++){
        table->item(i, 0)->setBackground(list[7*i].toInt()==1 ? Qt::red : Qt::white);
        table->item(i, 1)->setBackground(list[7*i+1].toInt()==1 ? Qt::blue : Qt::white);
        table->item(i, 2)->setText(QString::number(list[7*i+2].toUInt()));
        table->item(i, 3)->setText(QString::number(list[7*i+3].toUInt(),2).rightJustified(tagSize, '0'));
        table->item(i, 4)->setText(QString::number(list[7*i+4].toUInt(),2).rightJustified(model->indexBits, '0'));
        table->item(i, 5)->setText(QString::number(list[7*i+5].toUInt(),2).rightJustified(model->logDataWordCount,'0'));
        table->item(i, 6)->setText(QString::number(list[7*i+6].toUInt()));
    }
    for(;i < 64; i++){
        table->item(i, 0)->setBackground(Qt::white);
        table->item(i, 1)->setBackground(Qt::white);
        table->item(i, 2)->setText("");
        table->item(i, 3)->setText("");
        table->item(i, 4)->setText("");
        table->item(i, 5)->setText("");
        table->item(i, 6)->setText("");
    }
}
void CacheView::updateWithSearch(){
    qDebug() << "GUI: Update with search button";
    updatedWithComboBox = false;

    QList<QVariant> list;
    list << comboBox->currentData();
    bool okay;
    list << tagEdit->text();
    list << indexEdit->text();
    list << offsetEdit->text();
    if(prevId != comboBox->currentData().toInt()){
        count =0;
        prevId = comboBox->currentData().toInt();
    }
    list << count;
    main->sendMessage(ThreadMessage(ThreadMessage::R_VIEW_CACHE,list)); 
}
void CacheView::updateWithComboBox(){
    qDebug() << "GUI: Update with combo box";
    updatedWithComboBox = true;
    QList<QVariant> list;
    list << comboBox->currentData();

    list << "";
    list << "";
    list << "";
    if(prevId != comboBox->currentData().toInt()){
        count =0;
        prevId = comboBox->currentData().toInt();
    }
    list << count;
    main->sendMessage(ThreadMessage(ThreadMessage::R_VIEW_CACHE, list));
}
void CacheView::handleNextButton(){
    qDebug() << "GUI: next button for cache pressed";

    count += 64;
    if(updatedWithComboBox){
        updateWithComboBox();
    }
    else{
        updateWithSearch();
    }
}
void CacheView::handlePrevButton(){
    qDebug() << "GUI: prev button for cache pressed";
    if(count > 0){
        count -= 64;
    }
    if(updatedWithComboBox){
        updateWithComboBox();
    }
    else{
        updateWithSearch();
    }
}
