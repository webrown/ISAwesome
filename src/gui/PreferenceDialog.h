#ifndef PREFERENCEDIALOG_H
#define PREFERENCEDIALOG_H

#include <QDialog>
#include "ui_preferencedialog.h"
#include <QStandardPaths>
#include "MainWindow.h"
class MainWindow;
class PreferenceDialog : public QDialog
{
    Q_OBJECT
    public:
        PreferenceDialog( QWidget *parent = 0);
        ~PreferenceDialog();

    public slots:
        void handleOpen_WorkDirectory();
        void accept();

    private:
        MainWindow* mainWindow;
        Ui::PreferenceDialog _ui;
};

#endif
