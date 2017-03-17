#ifndef NEWCACHEDIALOG_H
#define NEWCACHEDIALOG_H

#include <QDialog>
#include <QStandardPaths>
#include <QFileDialog>
#include <cstdlib>
#include <QDebug>
#include "ui_newcachedialog.h"
#include "ui_newfiledialog.h"
#include "../memory/Cache.h"

class CacheInfo{
    public:
    Cache *next = NULL, *prev = NULL;
    int indexBits, logDataWordCount, logAssociativity;
    double delay;
};

class NewCacheDialog : public QDialog
{
    Q_OBJECT
    public:
        NewCacheDialog(Cache* topCache, QWidget *parent = 0);
        ~NewCacheDialog();
        CacheInfo getCacheInfo();
        QList<Cache *> list;

    public slots:
        void update(QSpinBox* box);
        void update(QComboBox* box); 

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

    private:
        Ui::NewFileDialog _ui;
};


#endif
