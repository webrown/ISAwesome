#ifndef REGISTERVIEW_H
#define REGISTERVIEW_H
class MainWindow;

#include <QTableWidget>
#include <QHeaderView>
#include <QDebug>
#include "../memory/Register.h"
#include <QComboBox>
#include "../computer/ThreadMessage.h"


class RegisterView : public QTableWidget
{
    Q_OBJECT

public:
    RegisterView(QWidget* parent = 0);
    ~RegisterView();
    void update();
    void init(MainWindow* main, QTableWidget* regTable, QComboBox* comboBox); 
    void showFlags();
    void showGeneral();
    void showVector(int n);
    void display(QList<QVariant> list);


public slots:
    void updateWithComboBox();

private:
    MainWindow* main;
    QTableWidget* regTable;
    QComboBox* comboBox;
};

#endif
