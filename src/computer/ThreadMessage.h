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
        R_ADD_CACHE,
        R_REMOVE_CACHE,
        R_CLEAR_CACHE,
        R_VIEW_PERFORMANCE, A_VIEW_PERFORMANCE,
        R_VIEW_BANANA, A_VIEW_BANANA,

        R_VIEW_CACHE, A_VIEW_CACHE,
        R_VIEW_MEMORY, A_VIEW_MEMORY,
        R_VIEW_REGISTER, A_VIEW_REGISTER,
        R_SAVE_STATE, A_SAVE_STATE,
        R_RESTORE_STATE, A_RESTORE_STATE,
        R_CHANGE_BANANA, A_CHANGE_BANANA

    };

    Type type;
    QVariant message;
    QVariant message2;
    ThreadMessage(){
    }
    ThreadMessage(Type type, QVariant message){
        this->type = type;
        this->message = message;
    }
    ThreadMessage(Type type, QVariant message, QVariant message2){
        this->type = type;
        this->message = message;
        this->message2 = message2;
    }
};

#endif

