#include "PerformanceView.h"
#include <QWidget>

PerformanceView::PerformanceView(QWidget* parent) : QTreeWidget(parent){
    QTreeWidgetItem * root = this->invisibleRootItem();
    add(root, "A", "B", 5);
}
PerformanceView::~PerformanceView(){
    //Do nothing
}

void PerformanceView::add(QTreeWidgetItem* parent, QString str, QString prefix, QVariant value){
    QFileInfo p(str);
    qDebug() << p.dir().canonicalPath();

    prefixMap[str] = prefix;
    defaultMap[str] = value;
    QTreeWidgetItem * item = new QTreeWidgetItem();
    itemMap[str] = item;
    if(value.type() == QVariant::Int){
        item->setText(0, prefix);
        item->setText(1, QString::number(value.toInt()));
    }
    else if(value.type() == QVariant::Double){
        item->setText(0, prefix);
        item->setText(1, QString::number(value.toDouble()));
    }
    parent->addChild(item);
}

void PerformanceView::clear(){
}
void PerformanceView::display(QMap<QString, QVariant>){
}
