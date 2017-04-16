#ifndef BANANAVIEW_H
#define BANANAVIEW_H

#include <QTableWidget>
#include "../computer/ThreadMessage.h"
#include <QDebug>
#include "../assembler/Disassembler.h"

class BananaView : public QTableWidget
{
    Q_OBJECT

    public:
        Disassembler disassembler;
        BananaView(QWidget* widget = 0);
        ~BananaView();
        void init();
        void display(QList<QVariant> list);


};
#endif
