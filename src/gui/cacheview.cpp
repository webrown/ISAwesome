#include "cacheview.h"
#include <QHeaderView>
#include <QDebug>
#include "../memory/Cache.h"

#define NUMBER_OF_DEFAULT_HEADERS 5


CacheView::CacheView(Cache* cache){
    this->cache = cache;
    cache->view = this;
    size_t dataWordCount =1<< cache->logDataWordCount;
    size_t ways = 1<< cache->logAssociativity;
    size_t maxIndex = 1 << cache->indexBits;


    int col = dataWordCount + NUMBER_OF_DEFAULT_HEADERS;
    int row = ways * maxIndex;
    this->setRowCount(row);
    this->setColumnCount(col);

    QStringList header;
    header << "Tag" <<"Index"<< "Dirty" <<"LRU" << "Valid";

    for(int i =0; i < dataWordCount; i ++){
        header << QString("Line %1").arg(i);
    }
    this->setHorizontalHeaderLabels(header);
    this->verticalHeader()->setVisible(false);
    update();
}
CacheView::~CacheView(){
}

void CacheView::update(){
    for(int ind = 0; ind < cache->contents->size(); ind++) {
        for(int way = 0; way < cache->contents->at(0)->size(); way++) {
            this->setItem(ind * cache->contents->at(0)->size() + way, 0, new QTableWidgetItem(QString::number(cache->tags->at(ind)->at(way))));
            this->setItem(ind * cache->contents->at(0)->size() + way, 1, new QTableWidgetItem(QString::number(ind)));
            this->setItem(ind * cache->contents->at(0)->size() + way, 2, new QTableWidgetItem(QString::number(cache->dirty->at(ind)->at(way))));
            this->setItem(ind * cache->contents->at(0)->size() + way, 3, new QTableWidgetItem(QString::number(cache->LRU->at(ind)->at(way))));
            this->setItem(ind * cache->contents->at(0)->size() + way, 4, new QTableWidgetItem(QString::number(cache->valid->at(ind)->at(way))));

            for(int offset = 0; offset < cache->contents->at(0)->at(0)->size(); offset++) {
                this->setItem(ind * cache->contents->at(0)->size() + way, NUMBER_OF_DEFAULT_HEADERS + offset, new QTableWidgetItem(QString::number(cache->contents->at(ind)->at(way)->at(offset))));
            }
        }
    }

}
