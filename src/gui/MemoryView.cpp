#include "MemoryView.h"
#include "MainWindow.h"

MemoryView::MemoryView(QWidget* widget) : QTableWidget(widget){
    //Do nothing
}
MemoryView::~MemoryView(){
    //Do nothing
}
void MemoryView::init(MainWindow* main, QTableWidget* memoryTable, HexSpinBox* spinBox, QPushButton* searchButton, QLineEdit* lineEdit){
    this->main = main;
    this->memoryTable = memoryTable;
    this->spinBox = spinBox;
    this->searchButton =searchButton;
    this->lineEdit = lineEdit;

    memoryTable->setRowCount(256);
    for(int row = 0; row < 256; row++){
        memoryTable->setItem(row, 0, new QTableWidgetItem());
        memoryTable->setItem(row, 1, new QTableWidgetItem());
        memoryTable->setItem(row, 2, new QTableWidgetItem());
        memoryTable->setItem(row, 3, new QTableWidgetItem());
    }
    connect(spinBox, SIGNAL (valueChanged(int)), this, SLOT(updateWithSpinBox()));
    connect(searchButton, SIGNAL (clicked()), this, SLOT(updateWithSearch()));

    update();
}

void MemoryView::updateWithSpinBox(){
    qDebug() << "GUI: Update with spin box";
    uint address = spinBox->hexValue();
    main->sendMessage(ThreadMessage(ThreadMessage::R_VIEW_MEMORY, address));
}
void MemoryView::updateWithSearch(){
    qDebug() << "GUI: Update with search";
    bool okay;
    uint searchAddress = lineEdit->text().toUInt(&okay, 16);
    if(okay == false){
        return;
    }
    // uint address = searchAddress >> 8;
    main->sendMessage(ThreadMessage(ThreadMessage::R_VIEW_MEMORY, searchAddress));
   
}
void MemoryView::display(QList<QVariant> list){
    uint address = list[0].toUInt();
    uint mask = (MainMemory::MEMORY_CHUNKS-1) << 8;
    uint chunkBit = ((mask & address) >> 8);
    uint x = (((1<<8)-1) & address) << 8;
    //check empty
    for(uint i = 0; i < 256; i++){
        uint content = list[i+1].toUInt();
        memoryTable->item(i, 0)->setText("0X" + QString::number(chunkBit + x + i,16).rightJustified(8,'0'));
        memoryTable->item(i, 1)->setText("0X" + QString::number(content, 16));
        memoryTable->item(i, 2)->setText(QString::number(content, 10));
        memoryTable->item(i, 3)->setText("0B" + QString::number(content, 2));
    }

    /* uint specific = searchAddress & ((1<<8)-1);
     * memoryTable->selectRow(specific); */
 
}
void MemoryView::update(){
    updateWithSpinBox();
}
