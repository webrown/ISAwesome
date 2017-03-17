#ifndef CACHEVIEW_H
#define CACHEVIEW_H

#include <QTableWidget>
#include <QHeaderView>
#include <QDebug>
#include "../memory/Cache.h"


class Cache;

class CacheView : public QTableWidget
{
    Q_OBJECT

public:
    Cache* cache;
    CacheView(Cache* cache);
    ~CacheView();
    void update();
};

#endif
