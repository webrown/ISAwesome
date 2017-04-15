#include "Tracker.h"
#include "MainWindow.h"

Tracker::Tracker(QWidget* parent): QListWidget(parent){
    //Do nothing
}
Tracker::~Tracker(){
    //Do nothing
}

void Tracker::init(MainWindow* main){
    this->main = main;
}
void Tracker::customContextMenu(QPoint point){
    qDebug() << "GUI: handle custom context menu for tracker";
    QPoint globalPos = this->mapToGlobal(point);

    QListWidgetItem* item = this->currentItem();
    if(item == NULL){
        return;
    }

    QMenu menu;
    QAction *addBreakAction = new QAction(tr("Break once"), &menu);
    addBreakAction->setEnabled(item->data(Qt::UserRole) != BreakPoint::BREAK);
    connect(addBreakAction,SIGNAL(triggered()), this, SLOT(handleAddBreak()));
    menu.addAction(addBreakAction);

    QAction *addBreakAllAction = new QAction(tr("Break all"), &menu);
    addBreakAllAction->setEnabled(item->data(Qt::UserRole) != BreakPoint::BREAK_ALL);
    connect(addBreakAllAction,SIGNAL(triggered()), this, SLOT(handleAddBreakAll()));
    menu.addAction(addBreakAllAction);

    QAction *addSkipAction = new QAction(tr("Skip"), &menu);
    addSkipAction->setEnabled(item->data(Qt::UserRole) != BreakPoint::SKIP); connect(addSkipAction,SIGNAL(triggered()), this, SLOT(handleAddSkip())); menu.addAction(addSkipAction);

    QAction *addSkipAllAction = new QAction(tr("Skip all"), &menu);
    addSkipAllAction->setEnabled(item->data(Qt::UserRole) != BreakPoint::SKIP_ALL);
    connect(addSkipAllAction,SIGNAL(triggered()), this, SLOT(handleAddSkipAll()));
    menu.addAction(addSkipAllAction);

    QAction *removeAction = new QAction(tr("No mark"), &menu);
    removeAction->setEnabled(item->data(Qt::UserRole) != BreakPoint::NONE);
    connect(removeAction,SIGNAL(triggered()), this, SLOT(handleRemove()));
    menu.addAction(removeAction);

    menu.exec(globalPos);
}

void Tracker::handleAddBreak(){
    qDebug() << "GUI: add break";
    QListWidgetItem* item = this->selectedItems().first();
    if(item == NULL){
        return;
    }
    item->setBackground(Qt::red);
    item->setData(Qt::UserRole, BreakPoint::BREAK);
    sendMessage(BreakPoint::BREAK, item);
}
void Tracker::handleAddBreakAll(){
    qDebug() << "GUI: add break all";
    QListWidgetItem* item = this->selectedItems().first();
    if(item == NULL){
        return;
    }
    item->setBackground(Qt::red);
    item->setData(Qt::UserRole, BreakPoint::BREAK_ALL);
    sendMessage(BreakPoint::BREAK_ALL, item);
}

void Tracker::handleAddSkip(){
    qDebug() << "GUI: add skip";
    QListWidgetItem* item = this->selectedItems().first();
    if(item == NULL){
        return;
    }
    item->setBackground(Qt::cyan);
    item->setData(Qt::UserRole, BreakPoint::SKIP);
    sendMessage(BreakPoint::SKIP, item);
}
void Tracker::handleAddSkipAll(){
    qDebug() << "GUI: add skip all";
    QListWidgetItem* item = this->selectedItems().first();
    if(item == NULL){
        return;
    }
    item->setBackground(Qt::cyan);
    item->setData(Qt::UserRole, BreakPoint::SKIP_ALL);
    sendMessage(BreakPoint::SKIP_ALL, item);
    
}
void Tracker::handleRemove(){
    qDebug() << "GUI: remove break";
    QListWidgetItem* item = this->selectedItems().first();
    if(item == NULL){
        return;
    }
    item->setBackground(Qt::BrushStyle::NoBrush);
    item->setData(Qt::UserRole, BreakPoint::NONE);
    sendMessage(BreakPoint::NONE, item);
}

void Tracker::feed(QList<QVariant> instructions){
    for(int i = 0; i < instructions.size(); i++){
        QString address = QString::number(INSTRUCTION_SIZE  * i,16).rightJustified(8, '0');
        QString instruction =disassembler.disassemble(instructions.at(i).toUInt()); 

        QListWidgetItem *newItem = new QListWidgetItem();
        newItem->setText(" " + address + "  " + instruction);
        QVariant bp (BreakPoint::NONE);
        newItem->setData(Qt::UserRole, BreakPoint::NONE);
        this->addItem(newItem);

        if(i == instructions.size()-1){
            newItem->setData(Qt::UserRole, BreakPoint::BREAK_ALL);
            newItem->setBackground(Qt::red);
            sendMessage(BreakPoint::BREAK_ALL, newItem);
        }
    }

}

void Tracker::clear(){
    markedItem = NULL;
    //clear
    QListWidget::clear();
}

void Tracker::mark(int index){
    if(markedItem != NULL){
        markedItem->setText(markedItem->text().remove(">"));
    }
    if(index < this->count()){
        this->setCurrentRow(index);
        markedItem = this->item(index);
        if(markedItem->data(Qt::UserRole) == BreakPoint::BREAK || markedItem->data(Qt::UserRole) == BreakPoint::SKIP){
            markedItem->setData(Qt::UserRole, BreakPoint::NONE);
            markedItem->setBackground(Qt::BrushStyle::NoBrush);
        }
        markedItem->setText(">" + markedItem->text());
    }
    else{
        markedItem = NULL;
    }
}
void Tracker::sendMessage(BreakPoint::BreakPoint type, QListWidgetItem* currItem){
    QList<QVariant> v;
    QVariant address = {currItem->text().remove(">").split(' ')[1].toUInt(Q_NULLPTR, 16)};
    v.append(address);
    v.append(type);
    main->sendMessage(ThreadMessage(ThreadMessage::R_ADDBREAK, v));
}
