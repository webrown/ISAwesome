#ifndef MEMORYVIEW_H
#define MEMORYVIEW_H

#include <QTableWidget>
#include <QHeaderView>
#include <QPushButton>
#include <QLineEdit>
#include <QDebug>
#include "../memory/MainMemory.h"
#include "HexSpinBox.h"


class MainMemory;

class MemoryView : public QTableWidget
{
    Q_OBJECT

public:
    MainMemory* memory;
    MemoryView();
    ~MemoryView();
    void update();
    void init(MainMemory* memory, QTableWidget* memoryTable, HexSpinBox* spinBox, QPushButton* searchButton, QLineEdit* lineEdit);

public slots:
    void updateWithSearch();
    void updateWithSpinBox();

private:
    QTableWidget* memoryTable;
    HexSpinBox* spinBox;
    QPushButton* searchButton;
    QLineEdit* lineEdit;
};

#endif
