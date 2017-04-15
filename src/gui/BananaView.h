#ifndef BANANAVIEW_H
#define BANANAVIEW_H

#include <QTableWidget>
#include "../computer/ThreadMessage.h"
#include <QDebug>

class BananaView : public QTableWidget
{
    Q_OBJECT

    public:
        BananaView(QWidget* widget = 0);
        ~BananaView();
        void init();
        void display(QList<QVariant> list);


};
#endif
