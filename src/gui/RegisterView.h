#ifndef REGISTERVIEW_H
#define REGISTERVIEW_H

#include <QTableWidget>
#include <QHeaderView>
#include <QDebug>
#include "../memory/Register.h"
#include <QComboBox>


class Register;

class RegisterView : public QTableWidget
{
    Q_OBJECT

public:
    Register* regs;
    RegisterView();
    ~RegisterView();
    void update();
    void init(Register* regs, QTableWidget* regTable, QComboBox* comboBox); 
    void showFlags();
    void showGeneral();
    void showVector(int n);


public slots:
    void updateWithComboBox();

private:
    QTableWidget* regTable;
    QComboBox* comboBox;
};

#endif
