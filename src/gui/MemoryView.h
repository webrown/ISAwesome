#ifndef MEMORYVIEW_H
#define MEMORYVIEW_H

class MainWindow;
#include <QTableWidget>
#include <QHeaderView>
#include <QPushButton>
#include <QLineEdit>
#include <QDebug>
#include "../memory/MainMemory.h"
#include "HexSpinBox.h"
#include "../computer/ThreadMessage.h"



class MemoryView : public QTableWidget
{
    Q_OBJECT

public:
    MemoryView(QWidget* widget = 0);
    ~MemoryView();
    void update();
    void init(MainWindow* main, QTableWidget* memoryTable, HexSpinBox* spinBox, QPushButton* searchButton, QLineEdit* lineEdit);
    void display(QList<QVariant> list);
    
public slots:
    void updateWithSearch();
    void updateWithSpinBox();

private:
    MainWindow* main;
    QTableWidget* memoryTable;
    HexSpinBox* spinBox;
    QPushButton* searchButton;
    QLineEdit* lineEdit;
};

#endif
