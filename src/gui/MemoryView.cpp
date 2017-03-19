#include "MemoryView.h"
MemoryView::MemoryView(){
    //Do nothing
}
MemoryView::~MemoryView(){
    //Do nothing
}
void MemoryView::init(MainMemory* memory, QTableWidget* memoryTable, HexSpinBox* spinBox, QPushButton* searchButton, QLineEdit* lineEdit){
    this->memory = memory;
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
    qDebug() << "Update with spin box";
    uint address = spinBox->hexValue();
    uint mask = (MainMemory::MEMORY_CHUNKS-1) << 8;
    uint chunkBit = ((mask & address) >> 8);
    uint x = (((1<<8)-1) & address) << 8;
    //check empty
    if(memory->_contents[chunkBit].size() ==0){
        for(int row = 0; row < 256; row++){
            memoryTable->item(row, 0)->setText("0X" + QString::number(chunkBit + x + row,16).rightJustified(8,'0'));
            memoryTable->item(row, 1)->setText("0X0");
            memoryTable->item(row, 2)->setText("0");
            memoryTable->item(row, 3)->setText("0B0");
        }
        return;
    }
    for(uint i = 0; i < 256; i++){
        uint content = memory->_contents[chunkBit][x + i].asUInt;
            memoryTable->item(i, 0)->setText("0X" + QString::number(chunkBit + x + i,16).rightJustified(8,'0'));
            memoryTable->item(i, 1)->setText("0X" + QString::number(content, 16));
            memoryTable->item(i, 2)->setText(QString::number(content, 10));
            memoryTable->item(i, 3)->setText("0B" + QString::number(content, 2));
    }
}
void MemoryView::updateWithSearch(){
    qDebug() << "Update with search";
    bool okay;
    uint searchAddress = lineEdit->text().toUInt(&okay, 16);
    if(okay == false){
        return;
    }
    uint address = searchAddress >> 8;
    uint mask = (MainMemory::MEMORY_CHUNKS-1) << 8;
    uint chunkBit = ((mask & address) >> 8);
    uint x = (((1<<8)-1) & address) << 8;
    //check empty
    if(memory->_contents[chunkBit].size() ==0){
        for(int row = 0; row < 256; row++){
            memoryTable->item(row, 0)->setText("0X" + QString::number(chunkBit + x + row,16).rightJustified(8,'0'));
            memoryTable->item(row, 1)->setText("0X0");
            memoryTable->item(row, 2)->setText("0");
            memoryTable->item(row, 3)->setText("0B0");
        }
    }
    else{
        for(uint i = 0; i < 256; i++){
            uint content = memory->_contents[chunkBit][x + i].asUInt;
            memoryTable->item(i, 0)->setText("0X" + QString::number(chunkBit + x + i,16).rightJustified(8,'0'));
            memoryTable->item(i, 1)->setText("0X" + QString::number(content, 16));
            memoryTable->item(i, 2)->setText(QString::number(content, 10));
            memoryTable->item(i, 3)->setText("0B" + QString::number(content, 2));
        }
    }

    uint specific = searchAddress & ((1<<8)-1);
    memoryTable->selectRow(specific);
    
}
void MemoryView::update(){
    updateWithSpinBox();
}
