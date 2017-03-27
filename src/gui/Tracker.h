#ifndef TRACKER_H
#define TRACKER_H
class MainWindow;
#include <QListWidget>
#include <QDebug>
#include <QMenu>
#include <QAction>
#include "../computer/ThreadMessage.h"
#include "../computer/BreakPoint.h"
#include "../assembler/Disassembler.h"

class Tracker: public QListWidget{
    Q_OBJECT
    public:
        Disassembler disassembler;

        Tracker(QWidget* parent = 0);
        ~Tracker();
        void init(MainWindow* main);
        void feed(QList<QVariant> instructions);
        void clear();
        void mark(int index);
        void sendMessage(BreakPoint::BreakPoint type,QListWidgetItem* currItem);
    public slots:
        void customContextMenu(QPoint p);
        void handleAddBreak();
        void handleAddBreakAll();
        void handleAddSkip();
        void handleAddSkipAll();
        void handleRemove();

    private:
        MainWindow* main;
        QListWidgetItem* markedItem = NULL;
};
#endif
