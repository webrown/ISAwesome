#ifndef PERFORMANCEVIEW_H
#define PERFORMANCEVIEW_H
#include <QTreeWidget>
#include <QVariant>
#include <QFileInfo>
#include <QDebug>
#include <QDir>
#include "../memory/MemoryStructure.h"
class PerformanceView: public QTreeWidget
{
    Q_OBJECT

    public:
        QMap<QString, QTreeWidgetItem*> itemMap;
        QMap<QString, QString> prefixMap;
        QMap<QString, QVariant> defaultMap;
        PerformanceView(QWidget* parent = 0);
        ~PerformanceView();
        void display(QMap<QString, QVariant>);
        void syncCache(MemoryStructure * str);
        

    private:
        void clear();
        QTreeWidgetItem* add(QTreeWidgetItem* parent, QString str, QString prefix, QVariant value);
};
#endif
