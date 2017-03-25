#ifndef THREADMESSAGEPOOL_H
#define THREADMESSAGEPOOL_H
#include <QList>
#include "ThreadMessage.h"
class ThreadMessagePool{
    public:
        static QList<ThreadMessage> queue;
        //static constructor and deconstructor for thread message pool
        //This must be used once
        static void __init(){
        }
        static void __destroy(){
        }
};
#endif
