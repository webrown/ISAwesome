#ifndef NEWFILEDIALOG_H
#define NEWFILEDIALOG_H

#include <QDialog>
#include "ui_newfiledialog.h"

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
