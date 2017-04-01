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
        enum Mode{
            DEC = 0, FLOAT = 1, INT =2
        };
        Mode mode = DEC;
    RegisterView(QWidget* parent = 0);
    ~RegisterView();
    void update();
    void init(MainWindow* main, QTableWidget* regTable, QComboBox* comboBox); 
    void showFlags();
    void showGeneral();
    void showVector(int n);
    void display(QList<QVariant> list);
    void color(int row, uint v);


public slots:
    void updateWithComboBox();
void handleHeader(int x);

private:
    MainWindow* main;
    QTableWidget* regTable;
    QComboBox* comboBox;
};

#endif
