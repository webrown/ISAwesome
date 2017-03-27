#include "MyQSpinBox.h"

MyQSpinBox::MyQSpinBox(QWidget * parent)
        : HexSpinBox(false, parent)
        , valueBeingSet(false)
{
    connect(this,SIGNAL(valueChanged(int)),this,SLOT(On_valueChanged(int)));
}

void    MyQSpinBox::setHexValue ( uint val )
{
    valueBeingSet = true;
    QSpinBox::setValue(val);
    valueBeingSet = false;
}

void MyQSpinBox::On_valueChanged(int val)
{
    if(!valueBeingSet)
        emit valueChangedNotBySet(val);
}
