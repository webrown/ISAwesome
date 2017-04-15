#include "BananaView.h"
BananaView:: BananaView(QWidget * widget) : QTableWidget(widget){
}
BananaView::~BananaView(){
    //Do nothing
}
void BananaView::init(){
    this->setRowCount(5);
    for(int row = 0; row < 5; row++){
        this->setItem(row, 0, new QTableWidgetItem());
        this->setItem(row, 1, new QTableWidgetItem());
        this->setItem(row, 2, new QTableWidgetItem());
        this->setItem(row, 3, new QTableWidgetItem());
        this->setItem(row, 4, new QTableWidgetItem());
    }

    this->setColumnWidth(3,100);

}

void BananaView::display(QList<QVariant> list){
    int rowSize = 5;
    int colSize = 5;

    qDebug() << this->item(0,0);
    for(int row = 0; row < rowSize; row++){
        qDebug() << "A";
        this->item(row,0) -> setBackground(list[row * rowSize + 0].toBool() ? Qt::red : Qt::white); 
        qDebug() << "A";

        this->item(row,1) -> setBackground(list[row * rowSize + 1].toBool() ? Qt::red : Qt::white); 

        this->item(row,2) -> setBackground(list[row * rowSize + 2].toBool() ? Qt::red : Qt::white); 
        this->item(row,3) -> setText(QString::number(list[row * rowSize + 3].toInt())); 

        this->item(row,4) -> setText(list[row * rowSize + 4].toString()); 

    }
}
