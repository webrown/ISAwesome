#ifndef CACHEVIEW_H
#define CACHEVIEW_H

#include <QTableWidget>
#include <QHeaderView>
#include <QPushButton>
#include <QDebug>
#include "../memory/Cache.h"
#include <QComboBox>
class MainWindow;


class CacheView : public QTableWidget
{
    Q_OBJECT

    public:
        CacheView(QWidget* parent = 0);
        ~CacheView();
        void update();
        void init(MainWindow* main, QTableWidget* memoryTable, QComboBox* comboBox, QPushButton* searchButton, QLineEdit* lineEdit, QLineEdit* indexEdit, QLineEdit* offsetEdit, QPushButton* nextButton, QPushButton* prevButton);
        void display(QList<QVariant> list);
        public slots:
            void updateWithComboBox();
        void updateWithSearch();
        void handleNextButton();
        void handlePrevButton();
    private:
        bool updatedWithComboBox = true;
        int prevId = 0;
        int count =0;
        MainWindow* main;
        QTableWidget* table;
        QComboBox* comboBox;
        QPushButton* searchButton;
        QLineEdit* tagEdit;
        QLineEdit* indexEdit;
        QLineEdit* offsetEdit;
        QPushButton* nextButton;
        QPushButton* prevButton;
};

#endif
