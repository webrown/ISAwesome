#ifndef MYQSPINBOX_H
#define MYQSPINBOX_H
//http://stackoverflow.com/questions/15762404/what-is-the-right-way-to-suppress-qt-signals-when-values-are-explicitely-set

#include "HexSpinBox.h"

class MyQSpinBox : public HexSpinBox
{
   Q_OBJECT
public:
    MyQSpinBox(QWidget * parent = 0 );
protected:
    bool valueBeingSet;
public slots:
    void setHexValue (uint val);
private slots:
    void On_valueChanged(int val);
signals:
    void valueChangedNotBySet(int val);
};  
#endif
