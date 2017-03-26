#ifndef THREADMESSAGE_H
#define THREADMESSAGE_H

#include <QVariant>

class ThreadMessage{
    public:
        //R_ means message moves from MainWindow to Computer
        //A_ means message moves from Computer to MainWindow
    enum Type{
        // Command was not valid
        // QVariant=STRING, cause
        A_ERROR,

        //Command was valid
        // QVaraint =None
        A_OKAY,

        R_INIT,  
        R_STOP, 
        R_STEP, 
        R_PAUSE,
        R_ADDBREAK,
        R_REMOVEBREAK,
        R_VIEW_CACHE, A_VIEW_CACHE,
        R_VIEW_MEMORY, A_VIEW_MEMORY,
        R_VIEW_REGISTER, A_VIEW_REGISTER
    };

    Type type;
    QVariant message;
    ThreadMessage(){
    }
    ThreadMessage(Type type, QVariant message){
        this->type = type;
        this->message = message;
    }
};

#endif

