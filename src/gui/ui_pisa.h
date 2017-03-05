/********************************************************************************
** Form generated from reading UI file 'pisa.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PISA_H
#define UI_PISA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSave_As;
    QAction *actionNew;
    QAction *actionPipeline;
    QAction *actionCode_Examiner;
    QAction *actionMemory;
    QAction *actionRegister;
    QAction *actionRun;
    QAction *actionConsole;
    QAction *actionAbout_PISA;
    QAction *actionPISA_Help;
    QAction *actionnew;
    QAction *actionopen;
    QAction *actionsave;
    QAction *actionstop;
    QAction *actionpause;
    QAction *actionforward;
    QAction *actionrewind;
    QAction *actionbuild;
    QAction *actionbuild_all;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionCut;
    QAction *actionCopy;
    QAction *actionPaste;
    QAction *actionDelete;
    QAction *actionSave_State;
    QAction *actionSave_State_As;
    QAction *actionLoad_state;
    QAction *actionRestore_State;
    QAction *actionNew_2;
    QAction *actionLoad;
    QAction *actionRestore;
    QAction *actionSave_As_2;
    QAction *actionAddCache;
    QAction *actionRemoveCache;
    QAction *actionClearCache;
    QAction *actionPredefined;
    QAction *actionDefault;
    QAction *actionFlushCache;
    QAction *acitonFlushAllCache;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QTabWidget *file_system;
    QWidget *tab_navigation;
    QWidget *tab_performance;
    QWidget *Track;
    QTabWidget *tabWidget_editor;
    QTabWidget *tabWidget_output;
    QWidget *tab_problems;
    QVBoxLayout *verticalLayout_5;
    QListWidget *listWidget;
    QWidget *tab_console;
    QVBoxLayout *verticalLayout_6;
    QPlainTextEdit *plainTextEdit;
    QWidget *tab_screen;
    QVBoxLayout *verticalLayout_4;
    QGraphicsView *graphicsView;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget_pipeline;
    QWidget *tab_scalar;
    QWidget *tab_vector;
    QTabWidget *tabWidget_memory;
    QWidget *tab_register;
    QVBoxLayout *verticalLayout_10;
    QTableWidget *tableWidget_6;
    QWidget *tab_flag;
    QVBoxLayout *verticalLayout_9;
    QTableWidget *tableWidget_8;
    QWidget *tab_vector1;
    QVBoxLayout *verticalLayout_8;
    QTableWidget *tableWidget_7;
    QWidget *tab_memory;
    QVBoxLayout *verticalLayout_7;
    QTableWidget *tableWidget_memory;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuEdt;
    QMenu *menuWindow;
    QMenu *menuWindow_2;
    QMenu *menu_Cache;
    QMenu *menuHelp;
    QToolBar *toolBar;
    QToolBar *toolBar_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1920, 1080);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(0, 0));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icon/img/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setIconSize(QSize(22, 22));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionSave_As = new QAction(MainWindow);
        actionSave_As->setObjectName(QStringLiteral("actionSave_As"));
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        actionPipeline = new QAction(MainWindow);
        actionPipeline->setObjectName(QStringLiteral("actionPipeline"));
        actionCode_Examiner = new QAction(MainWindow);
        actionCode_Examiner->setObjectName(QStringLiteral("actionCode_Examiner"));
        actionMemory = new QAction(MainWindow);
        actionMemory->setObjectName(QStringLiteral("actionMemory"));
        actionRegister = new QAction(MainWindow);
        actionRegister->setObjectName(QStringLiteral("actionRegister"));
        actionRun = new QAction(MainWindow);
        actionRun->setObjectName(QStringLiteral("actionRun"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/menu_icon/img/play.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRun->setIcon(icon1);
        actionConsole = new QAction(MainWindow);
        actionConsole->setObjectName(QStringLiteral("actionConsole"));
        actionAbout_PISA = new QAction(MainWindow);
        actionAbout_PISA->setObjectName(QStringLiteral("actionAbout_PISA"));
        actionPISA_Help = new QAction(MainWindow);
        actionPISA_Help->setObjectName(QStringLiteral("actionPISA_Help"));
        actionnew = new QAction(MainWindow);
        actionnew->setObjectName(QStringLiteral("actionnew"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/menu_icon/img/new.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionnew->setIcon(icon2);
        actionopen = new QAction(MainWindow);
        actionopen->setObjectName(QStringLiteral("actionopen"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/menu_icon/img/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionopen->setIcon(icon3);
        actionsave = new QAction(MainWindow);
        actionsave->setObjectName(QStringLiteral("actionsave"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/menu_icon/img/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionsave->setIcon(icon4);
        actionstop = new QAction(MainWindow);
        actionstop->setObjectName(QStringLiteral("actionstop"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/menu_icon/img/stop.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionstop->setIcon(icon5);
        actionpause = new QAction(MainWindow);
        actionpause->setObjectName(QStringLiteral("actionpause"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/menu_icon/img/pause.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionpause->setIcon(icon6);
        actionforward = new QAction(MainWindow);
        actionforward->setObjectName(QStringLiteral("actionforward"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/menu_icon/img/forward.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionforward->setIcon(icon7);
        actionrewind = new QAction(MainWindow);
        actionrewind->setObjectName(QStringLiteral("actionrewind"));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/menu_icon/img/backward.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionrewind->setIcon(icon8);
        actionbuild = new QAction(MainWindow);
        actionbuild->setObjectName(QStringLiteral("actionbuild"));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/menu_icon/img/build.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionbuild->setIcon(icon9);
        actionbuild_all = new QAction(MainWindow);
        actionbuild_all->setObjectName(QStringLiteral("actionbuild_all"));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/menu_icon/img/build_all.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionbuild_all->setIcon(icon10);
        actionUndo = new QAction(MainWindow);
        actionUndo->setObjectName(QStringLiteral("actionUndo"));
        actionRedo = new QAction(MainWindow);
        actionRedo->setObjectName(QStringLiteral("actionRedo"));
        actionCut = new QAction(MainWindow);
        actionCut->setObjectName(QStringLiteral("actionCut"));
        actionCopy = new QAction(MainWindow);
        actionCopy->setObjectName(QStringLiteral("actionCopy"));
        actionPaste = new QAction(MainWindow);
        actionPaste->setObjectName(QStringLiteral("actionPaste"));
        actionDelete = new QAction(MainWindow);
        actionDelete->setObjectName(QStringLiteral("actionDelete"));
        actionSave_State = new QAction(MainWindow);
        actionSave_State->setObjectName(QStringLiteral("actionSave_State"));
        actionSave_State_As = new QAction(MainWindow);
        actionSave_State_As->setObjectName(QStringLiteral("actionSave_State_As"));
        actionLoad_state = new QAction(MainWindow);
        actionLoad_state->setObjectName(QStringLiteral("actionLoad_state"));
        actionRestore_State = new QAction(MainWindow);
        actionRestore_State->setObjectName(QStringLiteral("actionRestore_State"));
        actionNew_2 = new QAction(MainWindow);
        actionNew_2->setObjectName(QStringLiteral("actionNew_2"));
        actionLoad = new QAction(MainWindow);
        actionLoad->setObjectName(QStringLiteral("actionLoad"));
        actionRestore = new QAction(MainWindow);
        actionRestore->setObjectName(QStringLiteral("actionRestore"));
        actionSave_As_2 = new QAction(MainWindow);
        actionSave_As_2->setObjectName(QStringLiteral("actionSave_As_2"));
        actionAddCache = new QAction(MainWindow);
        actionAddCache->setObjectName(QStringLiteral("actionAddCache"));
        actionRemoveCache = new QAction(MainWindow);
        actionRemoveCache->setObjectName(QStringLiteral("actionRemoveCache"));
        actionClearCache = new QAction(MainWindow);
        actionClearCache->setObjectName(QStringLiteral("actionClearCache"));
        actionPredefined = new QAction(MainWindow);
        actionPredefined->setObjectName(QStringLiteral("actionPredefined"));
        actionDefault = new QAction(MainWindow);
        actionDefault->setObjectName(QStringLiteral("actionDefault"));
        actionFlushCache = new QAction(MainWindow);
        actionFlushCache->setObjectName(QStringLiteral("actionFlushCache"));
        acitonFlushAllCache = new QAction(MainWindow);
        acitonFlushAllCache->setObjectName(QStringLiteral("acitonFlushAllCache"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetNoConstraint);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        file_system = new QTabWidget(centralwidget);
        file_system->setObjectName(QStringLiteral("file_system"));
        file_system->setTabShape(QTabWidget::Triangular);
        tab_navigation = new QWidget();
        tab_navigation->setObjectName(QStringLiteral("tab_navigation"));
        file_system->addTab(tab_navigation, QString());
        tab_performance = new QWidget();
        tab_performance->setObjectName(QStringLiteral("tab_performance"));
        sizePolicy.setHeightForWidth(tab_performance->sizePolicy().hasHeightForWidth());
        tab_performance->setSizePolicy(sizePolicy);
        file_system->addTab(tab_performance, QString());
        Track = new QWidget();
        Track->setObjectName(QStringLiteral("Track"));
        file_system->addTab(Track, QString());

        horizontalLayout_2->addWidget(file_system);

        tabWidget_editor = new QTabWidget(centralwidget);
        tabWidget_editor->setObjectName(QStringLiteral("tabWidget_editor"));
        sizePolicy.setHeightForWidth(tabWidget_editor->sizePolicy().hasHeightForWidth());
        tabWidget_editor->setSizePolicy(sizePolicy);
        tabWidget_editor->setTabsClosable(true);

        horizontalLayout_2->addWidget(tabWidget_editor);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 3);

        verticalLayout_2->addLayout(horizontalLayout_2);

        tabWidget_output = new QTabWidget(centralwidget);
        tabWidget_output->setObjectName(QStringLiteral("tabWidget_output"));
        tabWidget_output->setEnabled(true);
        sizePolicy.setHeightForWidth(tabWidget_output->sizePolicy().hasHeightForWidth());
        tabWidget_output->setSizePolicy(sizePolicy);
        tabWidget_output->setMaximumSize(QSize(16777215, 16777215));
        tab_problems = new QWidget();
        tab_problems->setObjectName(QStringLiteral("tab_problems"));
        sizePolicy.setHeightForWidth(tab_problems->sizePolicy().hasHeightForWidth());
        tab_problems->setSizePolicy(sizePolicy);
        verticalLayout_5 = new QVBoxLayout(tab_problems);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        listWidget = new QListWidget(tab_problems);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setFrameShape(QFrame::StyledPanel);
        listWidget->setFrameShadow(QFrame::Raised);

        verticalLayout_5->addWidget(listWidget);

        tabWidget_output->addTab(tab_problems, QString());
        tab_console = new QWidget();
        tab_console->setObjectName(QStringLiteral("tab_console"));
        sizePolicy.setHeightForWidth(tab_console->sizePolicy().hasHeightForWidth());
        tab_console->setSizePolicy(sizePolicy);
        verticalLayout_6 = new QVBoxLayout(tab_console);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        plainTextEdit = new QPlainTextEdit(tab_console);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));
        plainTextEdit->setFrameShape(QFrame::StyledPanel);
        plainTextEdit->setFrameShadow(QFrame::Raised);

        verticalLayout_6->addWidget(plainTextEdit);

        tabWidget_output->addTab(tab_console, QString());
        tab_screen = new QWidget();
        tab_screen->setObjectName(QStringLiteral("tab_screen"));
        sizePolicy.setHeightForWidth(tab_screen->sizePolicy().hasHeightForWidth());
        tab_screen->setSizePolicy(sizePolicy);
        verticalLayout_4 = new QVBoxLayout(tab_screen);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        graphicsView = new QGraphicsView(tab_screen);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setFrameShape(QFrame::StyledPanel);
        graphicsView->setFrameShadow(QFrame::Raised);

        verticalLayout_4->addWidget(graphicsView);

        tabWidget_output->addTab(tab_screen, QString());

        verticalLayout_2->addWidget(tabWidget_output);

        verticalLayout_2->setStretch(0, 3);
        verticalLayout_2->setStretch(1, 1);

        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetNoConstraint);
        tabWidget_pipeline = new QTabWidget(centralwidget);
        tabWidget_pipeline->setObjectName(QStringLiteral("tabWidget_pipeline"));
        tabWidget_pipeline->setStyleSheet(QStringLiteral("QTabBar::tab { height: 160px; }"));
        tabWidget_pipeline->setTabPosition(QTabWidget::West);
        tabWidget_pipeline->setTabShape(QTabWidget::Triangular);
        tabWidget_pipeline->setDocumentMode(true);
        tabWidget_pipeline->setTabBarAutoHide(false);
        tab_scalar = new QWidget();
        tab_scalar->setObjectName(QStringLiteral("tab_scalar"));
        tabWidget_pipeline->addTab(tab_scalar, QString());
        tab_vector = new QWidget();
        tab_vector->setObjectName(QStringLiteral("tab_vector"));
        tabWidget_pipeline->addTab(tab_vector, QString());

        verticalLayout->addWidget(tabWidget_pipeline);

        tabWidget_memory = new QTabWidget(centralwidget);
        tabWidget_memory->setObjectName(QStringLiteral("tabWidget_memory"));
        tab_register = new QWidget();
        tab_register->setObjectName(QStringLiteral("tab_register"));
        verticalLayout_10 = new QVBoxLayout(tab_register);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        tableWidget_6 = new QTableWidget(tab_register);
        if (tableWidget_6->columnCount() < 5)
            tableWidget_6->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_6->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_6->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_6->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_6->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_6->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tableWidget_6->setObjectName(QStringLiteral("tableWidget_6"));
        tableWidget_6->setFrameShape(QFrame::NoFrame);
        tableWidget_6->verticalHeader()->setVisible(false);

        verticalLayout_10->addWidget(tableWidget_6);

        tabWidget_memory->addTab(tab_register, QString());
        tab_flag = new QWidget();
        tab_flag->setObjectName(QStringLiteral("tab_flag"));
        verticalLayout_9 = new QVBoxLayout(tab_flag);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        tableWidget_8 = new QTableWidget(tab_flag);
        if (tableWidget_8->columnCount() < 5)
            tableWidget_8->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_8->setHorizontalHeaderItem(0, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget_8->setHorizontalHeaderItem(1, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget_8->setHorizontalHeaderItem(2, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget_8->setHorizontalHeaderItem(3, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget_8->setHorizontalHeaderItem(4, __qtablewidgetitem9);
        tableWidget_8->setObjectName(QStringLiteral("tableWidget_8"));
        tableWidget_8->setFrameShape(QFrame::NoFrame);
        tableWidget_8->verticalHeader()->setVisible(false);

        verticalLayout_9->addWidget(tableWidget_8);

        tabWidget_memory->addTab(tab_flag, QString());
        tab_vector1 = new QWidget();
        tab_vector1->setObjectName(QStringLiteral("tab_vector1"));
        verticalLayout_8 = new QVBoxLayout(tab_vector1);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        tableWidget_7 = new QTableWidget(tab_vector1);
        if (tableWidget_7->columnCount() < 5)
            tableWidget_7->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget_7->setHorizontalHeaderItem(0, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget_7->setHorizontalHeaderItem(1, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget_7->setHorizontalHeaderItem(2, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget_7->setHorizontalHeaderItem(3, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget_7->setHorizontalHeaderItem(4, __qtablewidgetitem14);
        tableWidget_7->setObjectName(QStringLiteral("tableWidget_7"));
        tableWidget_7->setFrameShape(QFrame::NoFrame);
        tableWidget_7->verticalHeader()->setVisible(false);

        verticalLayout_8->addWidget(tableWidget_7);

        tabWidget_memory->addTab(tab_vector1, QString());
        tab_memory = new QWidget();
        tab_memory->setObjectName(QStringLiteral("tab_memory"));
        verticalLayout_7 = new QVBoxLayout(tab_memory);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        tableWidget_memory = new QTableWidget(tab_memory);
        if (tableWidget_memory->columnCount() < 5)
            tableWidget_memory->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidget_memory->setHorizontalHeaderItem(0, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidget_memory->setHorizontalHeaderItem(1, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableWidget_memory->setHorizontalHeaderItem(2, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tableWidget_memory->setHorizontalHeaderItem(3, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tableWidget_memory->setHorizontalHeaderItem(4, __qtablewidgetitem19);
        tableWidget_memory->setObjectName(QStringLiteral("tableWidget_memory"));
        tableWidget_memory->setFrameShape(QFrame::NoFrame);
        tableWidget_memory->setRowCount(0);
        tableWidget_memory->verticalHeader()->setVisible(false);

        verticalLayout_7->addWidget(tableWidget_memory);

        tabWidget_memory->addTab(tab_memory, QString());

        verticalLayout->addWidget(tabWidget_memory);

        verticalLayout->setStretch(0, 3);
        verticalLayout->setStretch(1, 6);

        horizontalLayout->addLayout(verticalLayout);

        horizontalLayout->setStretch(0, 8);
        horizontalLayout->setStretch(1, 5);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1920, 30));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuEdt = new QMenu(menubar);
        menuEdt->setObjectName(QStringLiteral("menuEdt"));
        menuWindow = new QMenu(menubar);
        menuWindow->setObjectName(QStringLiteral("menuWindow"));
        menuWindow_2 = new QMenu(menubar);
        menuWindow_2->setObjectName(QStringLiteral("menuWindow_2"));
        menu_Cache = new QMenu(menuWindow_2);
        menu_Cache->setObjectName(QStringLiteral("menu_Cache"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        MainWindow->setMenuBar(menubar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);
        toolBar_2 = new QToolBar(MainWindow);
        toolBar_2->setObjectName(QStringLiteral("toolBar_2"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar_2);
        QWidget::setTabOrder(tabWidget_pipeline, tabWidget_memory);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuEdt->menuAction());
        menubar->addAction(menuWindow->menuAction());
        menubar->addAction(menuWindow_2->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addSeparator();
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSave_As);
        menuFile->addSeparator();
        menuFile->addAction(actionLoad_state);
        menuFile->addAction(actionRestore_State);
        menuEdt->addAction(actionUndo);
        menuEdt->addAction(actionRedo);
        menuEdt->addSeparator();
        menuEdt->addAction(actionCut);
        menuEdt->addAction(actionCopy);
        menuEdt->addAction(actionPaste);
        menuEdt->addAction(actionDelete);
        menuWindow_2->addAction(menu_Cache->menuAction());
        menuWindow_2->addAction(actionPipeline);
        menuWindow_2->addAction(actionCode_Examiner);
        menuWindow_2->addAction(actionMemory);
        menuWindow_2->addAction(actionRegister);
        menuWindow_2->addAction(actionConsole);
        menu_Cache->addAction(actionPredefined);
        menu_Cache->addSeparator();
        menu_Cache->addAction(actionAddCache);
        menu_Cache->addAction(actionRemoveCache);
        menu_Cache->addAction(actionClearCache);
        menu_Cache->addSeparator();
        menu_Cache->addAction(actionFlushCache);
        menu_Cache->addAction(acitonFlushAllCache);
        menuHelp->addAction(actionPISA_Help);
        menuHelp->addAction(actionAbout_PISA);
        toolBar->addAction(actionnew);
        toolBar->addAction(actionopen);
        toolBar->addAction(actionsave);
        toolBar->addSeparator();
        toolBar->addAction(actionRun);
        toolBar->addAction(actionpause);
        toolBar->addAction(actionstop);
        toolBar->addSeparator();
        toolBar->addAction(actionbuild);
        toolBar->addAction(actionbuild_all);
        toolBar->addSeparator();
        toolBar->addAction(actionrewind);
        toolBar->addAction(actionforward);
        toolBar->addSeparator();

        retranslateUi(MainWindow);

        file_system->setCurrentIndex(2);
        tabWidget_editor->setCurrentIndex(-1);
        tabWidget_output->setCurrentIndex(2);
        tabWidget_pipeline->setCurrentIndex(1);
        tabWidget_memory->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actionOpen->setText(QApplication::translate("MainWindow", "&Open", Q_NULLPTR));
        actionSave->setText(QApplication::translate("MainWindow", "&Save", Q_NULLPTR));
        actionSave_As->setText(QApplication::translate("MainWindow", "Sa&ve As", Q_NULLPTR));
        actionNew->setText(QApplication::translate("MainWindow", "&New", Q_NULLPTR));
        actionPipeline->setText(QApplication::translate("MainWindow", "&Pipeline", Q_NULLPTR));
        actionCode_Examiner->setText(QApplication::translate("MainWindow", "Code &Examiner", Q_NULLPTR));
        actionMemory->setText(QApplication::translate("MainWindow", "&Memory", Q_NULLPTR));
        actionRegister->setText(QApplication::translate("MainWindow", "&Register", Q_NULLPTR));
        actionRun->setText(QApplication::translate("MainWindow", "Run", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionRun->setToolTip(QApplication::translate("MainWindow", "Run Program", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionConsole->setText(QApplication::translate("MainWindow", "C&onsole", Q_NULLPTR));
        actionAbout_PISA->setText(QApplication::translate("MainWindow", "&About PISA", Q_NULLPTR));
        actionPISA_Help->setText(QApplication::translate("MainWindow", "&PISA Help", Q_NULLPTR));
        actionnew->setText(QApplication::translate("MainWindow", "new", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionnew->setToolTip(QApplication::translate("MainWindow", "Create New File", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionopen->setText(QApplication::translate("MainWindow", "open", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionopen->setToolTip(QApplication::translate("MainWindow", "Open File", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionsave->setText(QApplication::translate("MainWindow", "Save", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionsave->setToolTip(QApplication::translate("MainWindow", "Save File", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionstop->setText(QApplication::translate("MainWindow", "stop", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionstop->setToolTip(QApplication::translate("MainWindow", "Stop Program", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionpause->setText(QApplication::translate("MainWindow", "pause", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionpause->setToolTip(QApplication::translate("MainWindow", "Pause Program", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionforward->setText(QApplication::translate("MainWindow", "forward", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionforward->setToolTip(QApplication::translate("MainWindow", "Forward Program", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionrewind->setText(QApplication::translate("MainWindow", "rewind", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionrewind->setToolTip(QApplication::translate("MainWindow", "Rewind Program", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionbuild->setText(QApplication::translate("MainWindow", "build", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionbuild->setToolTip(QApplication::translate("MainWindow", "Build Current File", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionbuild_all->setText(QApplication::translate("MainWindow", "build all", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionbuild_all->setToolTip(QApplication::translate("MainWindow", "Build All Files", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionUndo->setText(QApplication::translate("MainWindow", "&Undo", Q_NULLPTR));
        actionRedo->setText(QApplication::translate("MainWindow", "&Redo", Q_NULLPTR));
        actionCut->setText(QApplication::translate("MainWindow", "&Cut", Q_NULLPTR));
        actionCopy->setText(QApplication::translate("MainWindow", "C&opy", Q_NULLPTR));
        actionPaste->setText(QApplication::translate("MainWindow", "&Paste", Q_NULLPTR));
        actionDelete->setText(QApplication::translate("MainWindow", "&Delete", Q_NULLPTR));
        actionSave_State->setText(QApplication::translate("MainWindow", "Save State", Q_NULLPTR));
        actionSave_State_As->setText(QApplication::translate("MainWindow", "Save State As", Q_NULLPTR));
        actionLoad_state->setText(QApplication::translate("MainWindow", "&Load State", Q_NULLPTR));
        actionRestore_State->setText(QApplication::translate("MainWindow", "&Restore State", Q_NULLPTR));
        actionNew_2->setText(QApplication::translate("MainWindow", "Add", Q_NULLPTR));
        actionLoad->setText(QApplication::translate("MainWindow", "Default", Q_NULLPTR));
        actionRestore->setText(QApplication::translate("MainWindow", "Save", Q_NULLPTR));
        actionSave_As_2->setText(QApplication::translate("MainWindow", "Save As", Q_NULLPTR));
        actionAddCache->setText(QApplication::translate("MainWindow", "&Add Cache", Q_NULLPTR));
        actionRemoveCache->setText(QApplication::translate("MainWindow", "&Remove Cache", Q_NULLPTR));
        actionClearCache->setText(QApplication::translate("MainWindow", "&Clear Cache", Q_NULLPTR));
        actionPredefined->setText(QApplication::translate("MainWindow", "&Predefined", Q_NULLPTR));
        actionDefault->setText(QApplication::translate("MainWindow", "&Default", Q_NULLPTR));
        actionFlushCache->setText(QApplication::translate("MainWindow", "&Flush", Q_NULLPTR));
        acitonFlushAllCache->setText(QApplication::translate("MainWindow", "F&lush All", Q_NULLPTR));
        file_system->setTabText(file_system->indexOf(tab_navigation), QApplication::translate("MainWindow", "Navigation", Q_NULLPTR));
        file_system->setTabText(file_system->indexOf(tab_performance), QApplication::translate("MainWindow", "Performance", Q_NULLPTR));
        file_system->setTabText(file_system->indexOf(Track), QApplication::translate("MainWindow", "Tracker", Q_NULLPTR));
        tabWidget_output->setTabText(tabWidget_output->indexOf(tab_problems), QApplication::translate("MainWindow", "Problems", Q_NULLPTR));
        tabWidget_output->setTabText(tabWidget_output->indexOf(tab_console), QApplication::translate("MainWindow", "Console", Q_NULLPTR));
        tabWidget_output->setTabText(tabWidget_output->indexOf(tab_screen), QApplication::translate("MainWindow", "Screen", Q_NULLPTR));
        tabWidget_pipeline->setTabText(tabWidget_pipeline->indexOf(tab_scalar), QApplication::translate("MainWindow", "Scalar", Q_NULLPTR));
        tabWidget_pipeline->setTabText(tabWidget_pipeline->indexOf(tab_vector), QApplication::translate("MainWindow", "Vector", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_6->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "Address", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_6->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "Binary", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_6->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "Decimal", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_6->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "Hex", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_6->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("MainWindow", "ASC II", Q_NULLPTR));
        tabWidget_memory->setTabText(tabWidget_memory->indexOf(tab_register), QApplication::translate("MainWindow", "Register", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_8->horizontalHeaderItem(0);
        ___qtablewidgetitem5->setText(QApplication::translate("MainWindow", "Address", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget_8->horizontalHeaderItem(1);
        ___qtablewidgetitem6->setText(QApplication::translate("MainWindow", "Binary", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget_8->horizontalHeaderItem(2);
        ___qtablewidgetitem7->setText(QApplication::translate("MainWindow", "Decimal", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget_8->horizontalHeaderItem(3);
        ___qtablewidgetitem8->setText(QApplication::translate("MainWindow", "Hex", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget_8->horizontalHeaderItem(4);
        ___qtablewidgetitem9->setText(QApplication::translate("MainWindow", "ASC II", Q_NULLPTR));
        tabWidget_memory->setTabText(tabWidget_memory->indexOf(tab_flag), QApplication::translate("MainWindow", "Flag", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget_7->horizontalHeaderItem(0);
        ___qtablewidgetitem10->setText(QApplication::translate("MainWindow", "Address", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget_7->horizontalHeaderItem(1);
        ___qtablewidgetitem11->setText(QApplication::translate("MainWindow", "Binary", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget_7->horizontalHeaderItem(2);
        ___qtablewidgetitem12->setText(QApplication::translate("MainWindow", "Decimal", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget_7->horizontalHeaderItem(3);
        ___qtablewidgetitem13->setText(QApplication::translate("MainWindow", "Hex", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget_7->horizontalHeaderItem(4);
        ___qtablewidgetitem14->setText(QApplication::translate("MainWindow", "ASC II", Q_NULLPTR));
        tabWidget_memory->setTabText(tabWidget_memory->indexOf(tab_vector1), QApplication::translate("MainWindow", "Vector", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidget_memory->horizontalHeaderItem(0);
        ___qtablewidgetitem15->setText(QApplication::translate("MainWindow", "Address", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidget_memory->horizontalHeaderItem(1);
        ___qtablewidgetitem16->setText(QApplication::translate("MainWindow", "Binary", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidget_memory->horizontalHeaderItem(2);
        ___qtablewidgetitem17->setText(QApplication::translate("MainWindow", "Decimal", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem18 = tableWidget_memory->horizontalHeaderItem(3);
        ___qtablewidgetitem18->setText(QApplication::translate("MainWindow", "Hex", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem19 = tableWidget_memory->horizontalHeaderItem(4);
        ___qtablewidgetitem19->setText(QApplication::translate("MainWindow", "ASC II", Q_NULLPTR));
        tabWidget_memory->setTabText(tabWidget_memory->indexOf(tab_memory), QApplication::translate("MainWindow", "Memory", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("MainWindow", "Fi&le", Q_NULLPTR));
        menuEdt->setTitle(QApplication::translate("MainWindow", "E&dt", Q_NULLPTR));
        menuWindow->setTitle(QApplication::translate("MainWindow", "V&iew", Q_NULLPTR));
        menuWindow_2->setTitle(QApplication::translate("MainWindow", "Mod&ule", Q_NULLPTR));
        menu_Cache->setTitle(QApplication::translate("MainWindow", "&Cache", Q_NULLPTR));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", Q_NULLPTR));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", Q_NULLPTR));
        toolBar_2->setWindowTitle(QApplication::translate("MainWindow", "toolBar_2", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PISA_H
