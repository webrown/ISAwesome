#ifndef NEWCACHEDIALOG_H
#define NEWCACHEDIALOG_H

#include <QDialog>
#include <QStandardPaths>
#include <QFileDialog>
#include <QErrorMessage>
#include <cstdlib>
#include <QMessageBox>
#include <QDebug>
#include "ui_newcachedialog.h"
#include "ui_newfiledialog.h"
#include "../memory/Cache.h"
#include "../memory/MemoryStructure.h"

class NewCacheDialog : public QDialog
{
    Q_OBJECT
    public:
        MemoryStructure* container;
        NewCacheDialog(MemoryStructure * container, QWidget *parent = 0);
        ~NewCacheDialog();

        //Internal use only
        Cache::Type getType();
        int getIndex();
        int getOffset();
        int getWay();
        double getDelay();
        int getNext();


    public slots:
        void accept();

    private:
        Ui::NewCacheDialog _ui;
};

class NewFileDialog : public QDialog
{
    Q_OBJECT
    public:
        explicit NewFileDialog(QString dir, QWidget *parent = 0);
        ~NewFileDialog();
        QString getFileName();

    public slots:
        void handleOpenButton();
        void handleRandomButton();
        void accept();

    private:
        Ui::NewFileDialog _ui;
};


#endif
