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
#include <QStyledItemDelegate>


class MemoryView : public QTableWidget
{
    Q_OBJECT

    public:
        enum Mode{
            DEC = 0, FLOAT = 1, INT =2
        };
        Mode mode = DEC;
        MemoryView(QWidget* widget = 0);
        ~MemoryView();
        void update();
        void init(MainWindow* main, QTableWidget* memoryTable, HexSpinBox* spinBox, QPushButton* searchButton, QLineEdit* lineEdit);
        void display(QList<QVariant> list);

        public slots:
            void updateWithSearch();
            void updateWithSpinBox();
            void handleHeader(int x);

    private:
        MainWindow* main;
        QTableWidget* memoryTable;
        HexSpinBox* spinBox;
        QPushButton* searchButton;
        QLineEdit* lineEdit;
};
#endif
