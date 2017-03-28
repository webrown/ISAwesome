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
        A_STATE_CHANGE,
        A_UPDATE,
        A_REMOVEBREAK,
        A_FEED,

        R_SET_PC,
        A_SET_PC,
        R_INIT,  
        R_STOP, 
        R_STEP, 
        R_PAUSE,
        R_ADDBREAK,
        R_VIEW_CACHE, A_VIEW_CACHE,
        R_VIEW_MEMORY, A_VIEW_MEMORY,
        R_VIEW_REGISTER, A_VIEW_REGISTER,
        R_SAVE_STATE, A_SAVE_STATE,
        R_RESTORE_STATE, A_RESTORE_STATE
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

