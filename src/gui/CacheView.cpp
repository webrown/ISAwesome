#include "CacheView.h"
#include "MainWindow.h"
#define NUMBER_OF_DEFAULT_HEADERS 5


CacheView::CacheView(QWidget * parent) : QTableWidget(parent){
}

CacheView::~CacheView(){
}

void CacheView::init(MainWindow* main, QTableWidget* memoryTable, QComboBox* comboBox, QPushButton* searchButton, QLineEdit* lineEdit, QLineEdit* indexEdit, QLineEdit* offsetEdit){
    this->main = main;
    this->table = memoryTable;
    this->comboBox = comboBox;
    this->searchButton =searchButton;
    this->tagEdit = lineEdit;
    this->indexEdit = indexEdit;
    this->offsetEdit = offsetEdit;

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

}




void CacheView::update(){
    updateWithComboBox();
}

void CacheView::display(QList<QVariant> list){
    int id = list.takeFirst().toInt();
    DummyMem* model = (DummyMem*) main->container.map[id];
    // qDebug() << list;
    // qDebug() << list.size();
    int i;
    table->setColumnHidden(2, model->logAssociativity==0);
    table->setColumnHidden(4, model->indexBits==0);
    table->setColumnHidden(5, model->logDataWordCount==0);
    
    int tagSize = 32-model->indexBits-model->logDataWordCount;
    int bitSize = fontMetrics().width('0');

    int tagWidth = qMax(bitSize * 3 + 15, tagSize * bitSize + 10);
    int indexWidth = qMax(bitSize * 5 + 15, model->indexBits * bitSize + 10);
    int offsetWidth = qMax(bitSize * 6 + 15, model->logDataWordCount * bitSize + 10);
    
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
    QList<QVariant> list;
    list << comboBox->currentData();
    bool okay;
    list << tagEdit->text();
    list << indexEdit->text();
    list << offsetEdit->text();
    main->sendMessage(ThreadMessage(ThreadMessage::R_VIEW_CACHE,list)); 
}
void CacheView::updateWithComboBox(){
    qDebug() << "GUI: Update with combo box";
    QList<QVariant> list;
    list << comboBox->currentData();
    main->sendMessage(ThreadMessage(ThreadMessage::R_VIEW_CACHE, list));
}
