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
#include "CacheModel.h"
#include "../memory/Cache.h"

class NewCacheDialog : public QDialog
{
    Q_OBJECT
    public:
        QList<CacheModel>* cacheModels;
        NewCacheDialog(QList<CacheModel>* cacheModels, QWidget *parent = 0);
        ~NewCacheDialog();
        CacheModel getModel();

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
