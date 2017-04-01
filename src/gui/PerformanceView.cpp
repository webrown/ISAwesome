#include "PerformanceView.h"
#include <QWidget>

PerformanceView::PerformanceView(QWidget* parent) : QTreeWidget(parent){
    QTreeWidgetItem * root = this->invisibleRootItem();

    //General
    QTreeWidgetItem * general = add(root, "/General", "General", {});

    QTreeWidgetItem * cycle = add(general, "/General/Cycle", "Cycle", {});
    add(cycle, "/General/Cycle/Total", "Total: ", 0);
    add(cycle, "/General/Cycle/CPI", "CPI: ", 0);
    add(cycle, "/General/Cycle/IPC", "IPC: ", 0);

    QTreeWidgetItem * time = add(general, "/General/Time", "Time", {});
    add(time, "/General/Time/Total", "Total: ", 0);
    add(time, "/General/Time/IPT", "IPT: ", 0);
    add(time, "/General/Time/CPT", "CPT: ", 0);


    //Instruction
    QTreeWidgetItem * instruction = add(root, "/Instruction", "Instruction", {});

    //ALU
    QTreeWidgetItem* alu = add(root, "/Alu", "ALU",{});

    //Memory
    QTreeWidgetItem* memory = add(root, "/Memory", "Memory",{});

    QTreeWidgetItem* reg = add(memory, "/Memory/Register", "Register",{});
    QTreeWidgetItem* main = add(memory, "/Memory/Ram", "RAM",{});



}
PerformanceView::~PerformanceView(){
    //Do nothing
}

QTreeWidgetItem* PerformanceView::add(QTreeWidgetItem* parent, QString str, QString prefix, QVariant value){
    prefixMap[str] = prefix;
    defaultMap[str] = value;
    QTreeWidgetItem * item = new QTreeWidgetItem();
    itemMap[str] = item;
    if(value.type() == QVariant::Int){
        item->setText(0, prefix + QString::number(value.toInt()));
    }
    else if(value.type() == QVariant::Double){
        item->setText(0, prefix + QString::number(value.toDouble()));
    }
    else{
        item->setText(0, prefix);
    }
    parent->addChild(item);
    return item;
}

void PerformanceView::clear(){
}
void PerformanceView::display(QMap<QString, QVariant>){
}
