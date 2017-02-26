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
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
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
    QAction *actionCache_View;
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
    QWidget *centralwidget;
    QTabWidget *tabWidget_editor;
    QTabWidget *tabWidget_output;
    QWidget *tab_problems;
    QListWidget *listWidget;
    QWidget *tab_console;
    QPlainTextEdit *plainTextEdit;
    QWidget *tab_screen;
    QGraphicsView *graphicsView;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QFrame *line;
    QTabWidget *tabWidget_pipeline;
    QWidget *tab_scalar;
    QWidget *tab_vector;
    QTabWidget *tabWidget_memory;
    QWidget *tab_register;
    QTableWidget *tableWidget_6;
    QWidget *tab_flag;
    QTableWidget *tableWidget_8;
    QWidget *tab_vector1;
    QTableWidget *tableWidget_7;
    QWidget *tab_memory;
    QTableWidget *tableWidget_memory;
    QLineEdit *lineEdit;
    QTabWidget *tabWidget_cache;
    QWidget *tab_cache_l1_i;
    QTableWidget *tableWidget;
    QWidget *tab_cache_l1_d;
    QTableWidget *tableWidget_3;
    QWidget *tab_cache_l2;
    QTableWidget *tableWidget_4;
    QWidget *tab_cache_l3;
    QTableWidget *tableWidget_5;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuEdt;
    QMenu *menuWindow;
    QMenu *menuWindow_2;
    QMenu *menuHelp;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1000, 750);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(1000, 0));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionSave_As = new QAction(MainWindow);
        actionSave_As->setObjectName(QStringLiteral("actionSave_As"));
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        actionCache_View = new QAction(MainWindow);
        actionCache_View->setObjectName(QStringLiteral("actionCache_View"));
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
        QIcon icon;
        icon.addFile(QStringLiteral(":/Menu_icon/play.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRun->setIcon(icon);
        actionConsole = new QAction(MainWindow);
        actionConsole->setObjectName(QStringLiteral("actionConsole"));
        actionAbout_PISA = new QAction(MainWindow);
        actionAbout_PISA->setObjectName(QStringLiteral("actionAbout_PISA"));
        actionPISA_Help = new QAction(MainWindow);
        actionPISA_Help->setObjectName(QStringLiteral("actionPISA_Help"));
        actionnew = new QAction(MainWindow);
        actionnew->setObjectName(QStringLiteral("actionnew"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/Menu_icon/new.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionnew->setIcon(icon1);
        actionopen = new QAction(MainWindow);
        actionopen->setObjectName(QStringLiteral("actionopen"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/Menu_icon/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionopen->setIcon(icon2);
        actionsave = new QAction(MainWindow);
        actionsave->setObjectName(QStringLiteral("actionsave"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/Menu_icon/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionsave->setIcon(icon3);
        actionstop = new QAction(MainWindow);
        actionstop->setObjectName(QStringLiteral("actionstop"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/Menu_icon/stop.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionstop->setIcon(icon4);
        actionpause = new QAction(MainWindow);
        actionpause->setObjectName(QStringLiteral("actionpause"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/Menu_icon/pause.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionpause->setIcon(icon5);
        actionforward = new QAction(MainWindow);
        actionforward->setObjectName(QStringLiteral("actionforward"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/Menu_icon/forward.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionforward->setIcon(icon6);
        actionrewind = new QAction(MainWindow);
        actionrewind->setObjectName(QStringLiteral("actionrewind"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/Menu_icon/backward.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionrewind->setIcon(icon7);
        actionbuild = new QAction(MainWindow);
        actionbuild->setObjectName(QStringLiteral("actionbuild"));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/Menu_icon/build.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionbuild->setIcon(icon8);
        actionbuild_all = new QAction(MainWindow);
        actionbuild_all->setObjectName(QStringLiteral("actionbuild_all"));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/Menu_icon/build_all.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionbuild_all->setIcon(icon9);
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
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        tabWidget_editor = new QTabWidget(centralwidget);
        tabWidget_editor->setObjectName(QStringLiteral("tabWidget_editor"));
        tabWidget_editor->setGeometry(QRect(0, 0, 491, 461));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tabWidget_editor->sizePolicy().hasHeightForWidth());
        tabWidget_editor->setSizePolicy(sizePolicy1);
        tabWidget_editor->setTabsClosable(true);
        tabWidget_output = new QTabWidget(centralwidget);
        tabWidget_output->setObjectName(QStringLiteral("tabWidget_output"));
        tabWidget_output->setGeometry(QRect(0, 460, 491, 221));
        tabWidget_output->setMaximumSize(QSize(491, 16777215));
        tab_problems = new QWidget();
        tab_problems->setObjectName(QStringLiteral("tab_problems"));
        listWidget = new QListWidget(tab_problems);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(0, 0, 483, 186));
        listWidget->setFrameShape(QFrame::HLine);
        tabWidget_output->addTab(tab_problems, QString());
        tab_console = new QWidget();
        tab_console->setObjectName(QStringLiteral("tab_console"));
        plainTextEdit = new QPlainTextEdit(tab_console);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(0, 0, 483, 186));
        plainTextEdit->setFrameShape(QFrame::NoFrame);
        tabWidget_output->addTab(tab_console, QString());
        tab_screen = new QWidget();
        tab_screen->setObjectName(QStringLiteral("tab_screen"));
        graphicsView = new QGraphicsView(tab_screen);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(110, 0, 256, 185));
        graphicsView->setFrameShape(QFrame::Panel);
        graphicsView->setFrameShadow(QFrame::Plain);
        tabWidget_output->addTab(tab_screen, QString());
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(490, 0, 511, 681));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetNoConstraint);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        line = new QFrame(verticalLayoutWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        tabWidget_pipeline = new QTabWidget(verticalLayoutWidget);
        tabWidget_pipeline->setObjectName(QStringLiteral("tabWidget_pipeline"));
        tabWidget_pipeline->setStyleSheet(QStringLiteral("QTabBar::tab { height: 110px; }"));
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

        tabWidget_memory = new QTabWidget(verticalLayoutWidget);
        tabWidget_memory->setObjectName(QStringLiteral("tabWidget_memory"));
        tab_register = new QWidget();
        tab_register->setObjectName(QStringLiteral("tab_register"));
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
        tableWidget_6->setGeometry(QRect(0, 0, 501, 192));
        tableWidget_6->setFrameShape(QFrame::NoFrame);
        tableWidget_6->verticalHeader()->setVisible(false);
        tabWidget_memory->addTab(tab_register, QString());
        tab_flag = new QWidget();
        tab_flag->setObjectName(QStringLiteral("tab_flag"));
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
        tableWidget_8->setGeometry(QRect(0, 0, 501, 192));
        tableWidget_8->setFrameShape(QFrame::NoFrame);
        tableWidget_8->verticalHeader()->setVisible(false);
        tabWidget_memory->addTab(tab_flag, QString());
        tab_vector1 = new QWidget();
        tab_vector1->setObjectName(QStringLiteral("tab_vector1"));
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
        tableWidget_7->setGeometry(QRect(0, 0, 501, 192));
        tableWidget_7->setFrameShape(QFrame::NoFrame);
        tableWidget_7->verticalHeader()->setVisible(false);
        tabWidget_memory->addTab(tab_vector1, QString());
        tab_memory = new QWidget();
        tab_memory->setObjectName(QStringLiteral("tab_memory"));
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
        tableWidget_memory->setGeometry(QRect(0, 0, 501, 191));
        tableWidget_memory->setFrameShape(QFrame::NoFrame);
        tableWidget_memory->setRowCount(0);
        tableWidget_memory->verticalHeader()->setVisible(false);
        lineEdit = new QLineEdit(tab_memory);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(400, 160, 101, 29));
        tabWidget_memory->addTab(tab_memory, QString());

        verticalLayout->addWidget(tabWidget_memory);

        tabWidget_cache = new QTabWidget(verticalLayoutWidget);
        tabWidget_cache->setObjectName(QStringLiteral("tabWidget_cache"));
        tab_cache_l1_i = new QWidget();
        tab_cache_l1_i->setObjectName(QStringLiteral("tab_cache_l1_i"));
        tableWidget = new QTableWidget(tab_cache_l1_i);
        if (tableWidget->columnCount() < 7)
            tableWidget->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem26);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(0, 0, 501, 192));
        tableWidget->setFrameShape(QFrame::NoFrame);
        tableWidget->verticalHeader()->setVisible(false);
        tabWidget_cache->addTab(tab_cache_l1_i, QString());
        tab_cache_l1_d = new QWidget();
        tab_cache_l1_d->setObjectName(QStringLiteral("tab_cache_l1_d"));
        tableWidget_3 = new QTableWidget(tab_cache_l1_d);
        if (tableWidget_3->columnCount() < 7)
            tableWidget_3->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(0, __qtablewidgetitem27);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(1, __qtablewidgetitem28);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(2, __qtablewidgetitem29);
        QTableWidgetItem *__qtablewidgetitem30 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(3, __qtablewidgetitem30);
        QTableWidgetItem *__qtablewidgetitem31 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(4, __qtablewidgetitem31);
        QTableWidgetItem *__qtablewidgetitem32 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(5, __qtablewidgetitem32);
        QTableWidgetItem *__qtablewidgetitem33 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(6, __qtablewidgetitem33);
        tableWidget_3->setObjectName(QStringLiteral("tableWidget_3"));
        tableWidget_3->setGeometry(QRect(0, 0, 501, 192));
        tableWidget_3->setFrameShape(QFrame::NoFrame);
        tableWidget_3->verticalHeader()->setVisible(false);
        tabWidget_cache->addTab(tab_cache_l1_d, QString());
        tab_cache_l2 = new QWidget();
        tab_cache_l2->setObjectName(QStringLiteral("tab_cache_l2"));
        tableWidget_4 = new QTableWidget(tab_cache_l2);
        if (tableWidget_4->columnCount() < 7)
            tableWidget_4->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem34 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(0, __qtablewidgetitem34);
        QTableWidgetItem *__qtablewidgetitem35 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(1, __qtablewidgetitem35);
        QTableWidgetItem *__qtablewidgetitem36 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(2, __qtablewidgetitem36);
        QTableWidgetItem *__qtablewidgetitem37 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(3, __qtablewidgetitem37);
        QTableWidgetItem *__qtablewidgetitem38 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(4, __qtablewidgetitem38);
        QTableWidgetItem *__qtablewidgetitem39 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(5, __qtablewidgetitem39);
        QTableWidgetItem *__qtablewidgetitem40 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(6, __qtablewidgetitem40);
        tableWidget_4->setObjectName(QStringLiteral("tableWidget_4"));
        tableWidget_4->setGeometry(QRect(0, 0, 501, 192));
        tableWidget_4->setFrameShape(QFrame::NoFrame);
        tableWidget_4->verticalHeader()->setVisible(false);
        tabWidget_cache->addTab(tab_cache_l2, QString());
        tab_cache_l3 = new QWidget();
        tab_cache_l3->setObjectName(QStringLiteral("tab_cache_l3"));
        tableWidget_5 = new QTableWidget(tab_cache_l3);
        if (tableWidget_5->columnCount() < 7)
            tableWidget_5->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem41 = new QTableWidgetItem();
        tableWidget_5->setHorizontalHeaderItem(0, __qtablewidgetitem41);
        QTableWidgetItem *__qtablewidgetitem42 = new QTableWidgetItem();
        tableWidget_5->setHorizontalHeaderItem(1, __qtablewidgetitem42);
        QTableWidgetItem *__qtablewidgetitem43 = new QTableWidgetItem();
        tableWidget_5->setHorizontalHeaderItem(2, __qtablewidgetitem43);
        QTableWidgetItem *__qtablewidgetitem44 = new QTableWidgetItem();
        tableWidget_5->setHorizontalHeaderItem(3, __qtablewidgetitem44);
        QTableWidgetItem *__qtablewidgetitem45 = new QTableWidgetItem();
        tableWidget_5->setHorizontalHeaderItem(4, __qtablewidgetitem45);
        QTableWidgetItem *__qtablewidgetitem46 = new QTableWidgetItem();
        tableWidget_5->setHorizontalHeaderItem(5, __qtablewidgetitem46);
        QTableWidgetItem *__qtablewidgetitem47 = new QTableWidgetItem();
        tableWidget_5->setHorizontalHeaderItem(6, __qtablewidgetitem47);
        tableWidget_5->setObjectName(QStringLiteral("tableWidget_5"));
        tableWidget_5->setGeometry(QRect(0, 0, 501, 192));
        tableWidget_5->setFrameShape(QFrame::NoFrame);
        tableWidget_5->verticalHeader()->setVisible(false);
        tabWidget_cache->addTab(tab_cache_l3, QString());

        verticalLayout->addWidget(tabWidget_cache);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1000, 30));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuEdt = new QMenu(menubar);
        menuEdt->setObjectName(QStringLiteral("menuEdt"));
        menuWindow = new QMenu(menubar);
        menuWindow->setObjectName(QStringLiteral("menuWindow"));
        menuWindow_2 = new QMenu(menubar);
        menuWindow_2->setObjectName(QStringLiteral("menuWindow_2"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        MainWindow->setMenuBar(menubar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);
        QWidget::setTabOrder(tabWidget_output, tabWidget_editor);
        QWidget::setTabOrder(tabWidget_editor, tabWidget_pipeline);
        QWidget::setTabOrder(tabWidget_pipeline, tabWidget_cache);
        QWidget::setTabOrder(tabWidget_cache, tabWidget_memory);

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
        menuWindow_2->addAction(actionCache_View);
        menuWindow_2->addAction(actionPipeline);
        menuWindow_2->addAction(actionCode_Examiner);
        menuWindow_2->addAction(actionMemory);
        menuWindow_2->addAction(actionRegister);
        menuWindow_2->addAction(actionConsole);
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

        tabWidget_editor->setCurrentIndex(-1);
        tabWidget_output->setCurrentIndex(1);
        tabWidget_pipeline->setCurrentIndex(1);
        tabWidget_memory->setCurrentIndex(3);
        tabWidget_cache->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actionOpen->setText(QApplication::translate("MainWindow", "&Open", Q_NULLPTR));
        actionSave->setText(QApplication::translate("MainWindow", "&Save", Q_NULLPTR));
        actionSave_As->setText(QApplication::translate("MainWindow", "Sa&ve As", Q_NULLPTR));
        actionNew->setText(QApplication::translate("MainWindow", "&New", Q_NULLPTR));
        actionCache_View->setText(QApplication::translate("MainWindow", "&Cache", Q_NULLPTR));
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
        QTableWidgetItem *___qtablewidgetitem20 = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem20->setText(QApplication::translate("MainWindow", "Tag", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem21 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem21->setText(QApplication::translate("MainWindow", "Set", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem22 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem22->setText(QApplication::translate("MainWindow", "LRU", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem23 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem23->setText(QApplication::translate("MainWindow", "Word0", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem24 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem24->setText(QApplication::translate("MainWindow", "Word1", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem25 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem25->setText(QApplication::translate("MainWindow", "Word2", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem26 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem26->setText(QApplication::translate("MainWindow", "Word3", Q_NULLPTR));
        tabWidget_cache->setTabText(tabWidget_cache->indexOf(tab_cache_l1_i), QApplication::translate("MainWindow", "Cache L1(I)", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem27 = tableWidget_3->horizontalHeaderItem(0);
        ___qtablewidgetitem27->setText(QApplication::translate("MainWindow", "Tag", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem28 = tableWidget_3->horizontalHeaderItem(1);
        ___qtablewidgetitem28->setText(QApplication::translate("MainWindow", "Set", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem29 = tableWidget_3->horizontalHeaderItem(2);
        ___qtablewidgetitem29->setText(QApplication::translate("MainWindow", "LRU", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem30 = tableWidget_3->horizontalHeaderItem(3);
        ___qtablewidgetitem30->setText(QApplication::translate("MainWindow", "Word0", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem31 = tableWidget_3->horizontalHeaderItem(4);
        ___qtablewidgetitem31->setText(QApplication::translate("MainWindow", "Word1", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem32 = tableWidget_3->horizontalHeaderItem(5);
        ___qtablewidgetitem32->setText(QApplication::translate("MainWindow", "Word2", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem33 = tableWidget_3->horizontalHeaderItem(6);
        ___qtablewidgetitem33->setText(QApplication::translate("MainWindow", "Word3", Q_NULLPTR));
        tabWidget_cache->setTabText(tabWidget_cache->indexOf(tab_cache_l1_d), QApplication::translate("MainWindow", "Cache L1(D)", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem34 = tableWidget_4->horizontalHeaderItem(0);
        ___qtablewidgetitem34->setText(QApplication::translate("MainWindow", "Tag", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem35 = tableWidget_4->horizontalHeaderItem(1);
        ___qtablewidgetitem35->setText(QApplication::translate("MainWindow", "Set", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem36 = tableWidget_4->horizontalHeaderItem(2);
        ___qtablewidgetitem36->setText(QApplication::translate("MainWindow", "LRU", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem37 = tableWidget_4->horizontalHeaderItem(3);
        ___qtablewidgetitem37->setText(QApplication::translate("MainWindow", "Word0", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem38 = tableWidget_4->horizontalHeaderItem(4);
        ___qtablewidgetitem38->setText(QApplication::translate("MainWindow", "Word1", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem39 = tableWidget_4->horizontalHeaderItem(5);
        ___qtablewidgetitem39->setText(QApplication::translate("MainWindow", "Word2", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem40 = tableWidget_4->horizontalHeaderItem(6);
        ___qtablewidgetitem40->setText(QApplication::translate("MainWindow", "Word3", Q_NULLPTR));
        tabWidget_cache->setTabText(tabWidget_cache->indexOf(tab_cache_l2), QApplication::translate("MainWindow", "Cache L2", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem41 = tableWidget_5->horizontalHeaderItem(0);
        ___qtablewidgetitem41->setText(QApplication::translate("MainWindow", "Tag", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem42 = tableWidget_5->horizontalHeaderItem(1);
        ___qtablewidgetitem42->setText(QApplication::translate("MainWindow", "Set", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem43 = tableWidget_5->horizontalHeaderItem(2);
        ___qtablewidgetitem43->setText(QApplication::translate("MainWindow", "LRU", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem44 = tableWidget_5->horizontalHeaderItem(3);
        ___qtablewidgetitem44->setText(QApplication::translate("MainWindow", "Word0", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem45 = tableWidget_5->horizontalHeaderItem(4);
        ___qtablewidgetitem45->setText(QApplication::translate("MainWindow", "Word1", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem46 = tableWidget_5->horizontalHeaderItem(5);
        ___qtablewidgetitem46->setText(QApplication::translate("MainWindow", "Word2", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem47 = tableWidget_5->horizontalHeaderItem(6);
        ___qtablewidgetitem47->setText(QApplication::translate("MainWindow", "Word3", Q_NULLPTR));
        tabWidget_cache->setTabText(tabWidget_cache->indexOf(tab_cache_l3), QApplication::translate("MainWindow", "Cache L3", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("MainWindow", "Fi&le", Q_NULLPTR));
        menuEdt->setTitle(QApplication::translate("MainWindow", "E&dt", Q_NULLPTR));
        menuWindow->setTitle(QApplication::translate("MainWindow", "V&iew", Q_NULLPTR));
        menuWindow_2->setTitle(QApplication::translate("MainWindow", "Wi&ndow", Q_NULLPTR));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", Q_NULLPTR));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PISA_H
