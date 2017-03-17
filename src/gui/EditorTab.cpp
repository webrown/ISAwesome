#include "EditorTab.h"
EditorTab::EditorTab(QWidget* parent):QTabWidget(parent){

}

//add page on editor
CodeEditor* EditorTab::newTab(QString fileName)
{
    QFile* file = new QFile(fileName);
    CodeEditor* widget = new CodeEditor(file);

    //connect undo and redo button
   connect(widget, SIGNAL(textChanged()), this, SLOT(editorModified()));
    
    QString _fileName = fileName.section("/",-1,-1);   
    addTab(widget, _fileName);  
    return widget;
}

CodeEditor* EditorTab::openTab(QString fileName){
    QFile file(fileName);
    if(file.exists() == false){
        qDebug() << "File doesn't exist!";
        exit(-1);
    }
    CodeEditor* widget = newTab(fileName);
    widget->read();
    return widget;
}

bool EditorTab::saveTab(){
    int index = this->currentIndex();
    if(index == -1){
        return false;
    }
    //update tab name
    QString title = this->tabText(index);
    if(title.endsWith("*")){
        title.remove(title.length()-1,1);
        this->setTabText(index, title);
    }

    //save file
    ((CodeEditor*)this->widget(index))->write();

}

bool EditorTab::saveAsTab(QString name){
    int index = this->currentIndex();
    if(index == -1){
        return false;
    }
    //update tab name
    QString title = this->tabText(index);
    if(title.endsWith("*")){
        title.remove(title.length()-1,1);
        this->setTabText(index, title);
    }

    //save file
    ((CodeEditor*)this->widget(index))->writeAs(name);

}
bool EditorTab::saveAllTab(){
    if(count() == 0){
        return false;
    }

    for(int index = 0; index < count(); index++){
        //update tab name
        QString title = this->tabText(index);
        if(title.endsWith("*")){
            title.remove(title.length()-1,1);
            this->setTabText(index, title);
        }

        //save file
        ((CodeEditor*)this->widget(index))->write();


    }
}
//close tab
void EditorTab::closeTab(int index){
    this->removeTab(index);
}


//editor is modified, we need to put * next to title
void EditorTab::editorModified()
{
        int index = this->currentIndex();
        QString title = this->tabText(index);
        if(!title.endsWith("*")){
            title = title + "*";
            this->setTabText(index,title);
        }
}


