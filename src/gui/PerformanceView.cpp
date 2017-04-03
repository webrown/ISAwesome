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
    add(instruction, "/Instruction/Total", "Total: ", {});

    //ALU
    QTreeWidgetItem* alu = add(root, "/Alu", "ALU",{});

    //Memory
    QTreeWidgetItem* memory = add(root, "/Memory", "Memory",{});

    QTreeWidgetItem* reg = add(memory, "/Memory/Register", "Register",{});
    QTreeWidgetItem* main = add(memory, "/Memory/Ram", "RAM",{});
    add(main, "/Memory/Ram/Size", "Size: 4GB", {});
    add(main, "/Memory/Ram/Delay", "Delay: ", {MAIN_MEMORY_DELAY});
    add(main, "/Memory/Ram/Page", "Page: ", {0});
    



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

void PerformanceView::syncCache(MemoryStructure * str){
    //It is very inefficient, but it won't be called during the run.
    QTreeWidgetItem * memory = itemMap["/Memory"];
    for(int i =memory->childCount() -1; i >= 0; i--){
        QTreeWidgetItem * child = memory->child(i);
        if(child->text(0).contains("Cache") == true){
            memory->removeChild(child);
        }
    }

    for(QPair<QString, int> pair : str->getIds()){
        QString entry = "/Memory/" + pair.first;
        QTreeWidgetItem * cache = add(memory, entry, pair.first, {});

        add(cache, entry + "/Id", "ID: ", pair.second); 
        //TODO calculate this plz
        add(cache, entry + "/Size", "Size: ", 1 << (str->map[pair.second]->indexBits + str->map[pair.second]->logDataWordCount + str->map[pair.second]->logAssociativity));
        add(cache, entry + "/IndexBit", "Indexes: ", (1 << str->map[pair.second]->indexBits));
        add(cache, entry + "/WordBit", "Words: ", (1 << str->map[pair.second]->logDataWordCount));
        add(cache, entry + "/WayBit", "Ways: ", (1 << str->map[pair.second]->logAssociativity));
        add(cache, entry + "/Delay", "Delay: ", str->map[pair.second]->delay);

        QTreeWidgetItem * stat = add(cache, entry +"/Stat", "Stat", {});
        add(stat, entry +"/Stat/HitRate", "Hit Rate: ", {0});
        add(stat, entry +"/Stat/HitCount", "H Count: ", {0});
        add(stat, entry +"/Stat/CompulsuryMiss", "C Miss: ", {0});
        add(stat, entry +"/Stat/ConflictMiss", "X Miss: ", {0});
    }
    //reorder ram   
    QTreeWidgetItem * ram = itemMap["/Memory/Ram"];
    int index = memory->indexOfChild(ram);
    memory->takeChild(index);
    memory->insertChild(memory->childCount(), ram);

}

void PerformanceView::clear(){
}
void PerformanceView::display(QMap<QString, QVariant> map){
    for(QString key : map.keys()){
        if(itemMap.contains(key)){
            if(map[key].type() == QVariant::Int){
                itemMap[key]->setText(0,prefixMap[key] + QString::number(map[key].toInt()));

            }
            else if(map[key].type() == QVariant::Double){
                itemMap[key]->setText(0, prefixMap[key] + QString::number(map[key].toDouble()));
            }
            else if(map[key].type() == QVariant::LongLong){
                itemMap[key]->setText(0, prefixMap[key] + QString::number(map[key].toLongLong()));
            }
            else{
                itemMap[key]->setText(0, prefixMap[key]);
            }
        }
        else{
            qDebug() << key;
            qDebug() << "Oops";
        }
    }
}
