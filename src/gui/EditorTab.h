#ifndef EDITORTAB_H
#define EDITORTAB_H

#include <QTableWidget>
#include "CodeEditor.h"

class EditorTab : public QTabWidget
{
    Q_OBJECT

    public:
        explicit EditorTab(QWidget* parent = 0);

        QString currentTitle();
        CodeEditor* currentEditor();
        bool isCurrentSaved();
            
        bool isEmpty();
        CodeEditor* newTab(QString fileName, bool open = false);
        CodeEditor* openTab(QString fileName);
        bool saveTab();
        bool saveAllTab();
        bool saveAsTab(QString name);

    public slots:
        void closeTab(int index);
            void editorModified();

};

#endif
