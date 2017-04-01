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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "CacheView.h"
#include "EditorTab.h"
#include "HexSpinBox.h"
#include "MemoryView.h"
#include "PerformanceView.h"
#include "RegisterView.h"
#include "Tracker.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionSave_As;
    QAction *actionPipeline;
    QAction *actionRun;
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
    QAction *actionSave_state;
    QAction *actionRestore_State;
    QAction *actionAddCache;
    QAction *actionRemoveCache;
    QAction *actionClearCache;
    QAction *actionPredefined;
    QAction *actionPreference;
    QAction *actionSave_all;
    QAction *actionUpload;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QTabWidget *leftBoard;
    QWidget *tab_navigation;
    QVBoxLayout *verticalLayout_3;
    QTreeView *fileSystemView;
    QWidget *tab_performance;
    QHBoxLayout *horizontalLayout_7;
    PerformanceView *treeWidget;
    QWidget *Track;
    QVBoxLayout *verticalLayout_8;
    Tracker *tracker;
    EditorTab *editorTab;
    QTabWidget *tabWidget_output;
    QWidget *tab_problems;
    QVBoxLayout *verticalLayout_5;
    QTableWidget *problemTable;
    QWidget *tab_console;
    QVBoxLayout *verticalLayout_6;
    QPlainTextEdit *consoleTextEdit;
    QWidget *tab_screen;
    QVBoxLayout *verticalLayout_4;
    QGraphicsView *graphicsView;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget_pipeline;
    QWidget *tab_scalar;
    QWidget *tab_vector;
    QTabWidget *tabWidget_memory;
    RegisterView *tab_register;
    QVBoxLayout *verticalLayout_10;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QComboBox *comboBox;
    QSpacerItem *horizontalSpacer_2;
    QTableWidget *tableWidget_6;
    CacheView *tab_cache;
    QVBoxLayout *verticalLayout_9;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QComboBox *cacheListBox;
    QLineEdit *tagLine;
    QLineEdit *indexLine;
    QLineEdit *offsetLine;
    QPushButton *pushButton_2;
    QTableWidget *tableWidget_7;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *prevButton;
    QPushButton *nextButton;
    MemoryView *tab_memory;
    QVBoxLayout *verticalLayout_7;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QLabel *label_3;
    HexSpinBox *spinBox;
    QSpacerItem *horizontalSpacer;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QTableWidget *tableWidget_memory;
    QWidget *widget;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuEdt;
    QMenu *menuWindow;
    QMenu *menuWindow_2;
    QMenu *menu_Cache;
    QMenu *menuHelp;
    QMenu *menuSettings;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1920, 1081);
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
        actionSave_As = new QAction(MainWindow);
        actionSave_As->setObjectName(QStringLiteral("actionSave_As"));
        actionPipeline = new QAction(MainWindow);
        actionPipeline->setObjectName(QStringLiteral("actionPipeline"));
        actionRun = new QAction(MainWindow);
        actionRun->setObjectName(QStringLiteral("actionRun"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/menu_icon2/img/play2.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRun->setIcon(icon1);
        actionAbout_PISA = new QAction(MainWindow);
        actionAbout_PISA->setObjectName(QStringLiteral("actionAbout_PISA"));
        actionPISA_Help = new QAction(MainWindow);
        actionPISA_Help->setObjectName(QStringLiteral("actionPISA_Help"));
        actionnew = new QAction(MainWindow);
        actionnew->setObjectName(QStringLiteral("actionnew"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/menu_icon2/img/new2.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionnew->setIcon(icon2);
        actionopen = new QAction(MainWindow);
        actionopen->setObjectName(QStringLiteral("actionopen"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/menu_icon2/img/open2.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionopen->setIcon(icon3);
        actionsave = new QAction(MainWindow);
        actionsave->setObjectName(QStringLiteral("actionsave"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/menu_icon2/img/save2.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionsave->setIcon(icon4);
        actionstop = new QAction(MainWindow);
        actionstop->setObjectName(QStringLiteral("actionstop"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/menu_icon2/img/stop2.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionstop->setIcon(icon5);
        actionpause = new QAction(MainWindow);
        actionpause->setObjectName(QStringLiteral("actionpause"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/menu_icon2/img/pause2.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionpause->setIcon(icon6);
        actionforward = new QAction(MainWindow);
        actionforward->setObjectName(QStringLiteral("actionforward"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/menu_icon2/img/forward2.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionforward->setIcon(icon7);
        actionrewind = new QAction(MainWindow);
        actionrewind->setObjectName(QStringLiteral("actionrewind"));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/menu_icon2/img/backward2.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionrewind->setIcon(icon8);
        actionbuild = new QAction(MainWindow);
        actionbuild->setObjectName(QStringLiteral("actionbuild"));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/menu_icon2/img/build2.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionbuild->setIcon(icon9);
        actionbuild_all = new QAction(MainWindow);
        actionbuild_all->setObjectName(QStringLiteral("actionbuild_all"));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/menu_icon2/img/build_all2.png"), QSize(), QIcon::Normal, QIcon::Off);
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
        actionSave_state = new QAction(MainWindow);
        actionSave_state->setObjectName(QStringLiteral("actionSave_state"));
        actionRestore_State = new QAction(MainWindow);
        actionRestore_State->setObjectName(QStringLiteral("actionRestore_State"));
        actionAddCache = new QAction(MainWindow);
        actionAddCache->setObjectName(QStringLiteral("actionAddCache"));
        actionRemoveCache = new QAction(MainWindow);
        actionRemoveCache->setObjectName(QStringLiteral("actionRemoveCache"));
        actionClearCache = new QAction(MainWindow);
        actionClearCache->setObjectName(QStringLiteral("actionClearCache"));
        actionPredefined = new QAction(MainWindow);
        actionPredefined->setObjectName(QStringLiteral("actionPredefined"));
        actionPreference = new QAction(MainWindow);
        actionPreference->setObjectName(QStringLiteral("actionPreference"));
        actionSave_all = new QAction(MainWindow);
        actionSave_all->setObjectName(QStringLiteral("actionSave_all"));
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/menu_icon2/img/save_all2.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave_all->setIcon(icon11);
        actionUpload = new QAction(MainWindow);
        actionUpload->setObjectName(QStringLiteral("actionUpload"));
        QIcon icon12;
        icon12.addFile(QStringLiteral(":/menu_icon2/img/upload2.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionUpload->setIcon(icon12);
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
        leftBoard = new QTabWidget(centralwidget);
        leftBoard->setObjectName(QStringLiteral("leftBoard"));
        leftBoard->setTabShape(QTabWidget::Triangular);
        tab_navigation = new QWidget();
        tab_navigation->setObjectName(QStringLiteral("tab_navigation"));
        verticalLayout_3 = new QVBoxLayout(tab_navigation);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        fileSystemView = new QTreeView(tab_navigation);
        fileSystemView->setObjectName(QStringLiteral("fileSystemView"));
        fileSystemView->setContextMenuPolicy(Qt::NoContextMenu);

        verticalLayout_3->addWidget(fileSystemView);

        leftBoard->addTab(tab_navigation, QString());
        tab_performance = new QWidget();
        tab_performance->setObjectName(QStringLiteral("tab_performance"));
        sizePolicy.setHeightForWidth(tab_performance->sizePolicy().hasHeightForWidth());
        tab_performance->setSizePolicy(sizePolicy);
        horizontalLayout_7 = new QHBoxLayout(tab_performance);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        treeWidget = new PerformanceView(tab_performance);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));

        horizontalLayout_7->addWidget(treeWidget);

        leftBoard->addTab(tab_performance, QString());
        Track = new QWidget();
        Track->setObjectName(QStringLiteral("Track"));
        verticalLayout_8 = new QVBoxLayout(Track);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        tracker = new Tracker(Track);
        tracker->setObjectName(QStringLiteral("tracker"));
        tracker->setContextMenuPolicy(Qt::CustomContextMenu);
        tracker->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tracker->setAlternatingRowColors(true);

        verticalLayout_8->addWidget(tracker);

        leftBoard->addTab(Track, QString());

        horizontalLayout_2->addWidget(leftBoard);

        editorTab = new EditorTab(centralwidget);
        editorTab->setObjectName(QStringLiteral("editorTab"));
        sizePolicy.setHeightForWidth(editorTab->sizePolicy().hasHeightForWidth());
        editorTab->setSizePolicy(sizePolicy);
        editorTab->setTabsClosable(true);

        horizontalLayout_2->addWidget(editorTab);

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
        problemTable = new QTableWidget(tab_problems);
        if (problemTable->columnCount() < 5)
            problemTable->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        problemTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        problemTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        problemTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        problemTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        problemTable->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        problemTable->setObjectName(QStringLiteral("problemTable"));
        problemTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        problemTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        problemTable->horizontalHeader()->setDefaultSectionSize(100);
        problemTable->horizontalHeader()->setMinimumSectionSize(45);
        problemTable->horizontalHeader()->setStretchLastSection(true);
        problemTable->verticalHeader()->setVisible(false);
        problemTable->verticalHeader()->setMinimumSectionSize(0);
        problemTable->verticalHeader()->setProperty("showSortIndicator", QVariant(true));
        problemTable->verticalHeader()->setStretchLastSection(false);

        verticalLayout_5->addWidget(problemTable);

        tabWidget_output->addTab(tab_problems, QString());
        tab_console = new QWidget();
        tab_console->setObjectName(QStringLiteral("tab_console"));
        sizePolicy.setHeightForWidth(tab_console->sizePolicy().hasHeightForWidth());
        tab_console->setSizePolicy(sizePolicy);
        verticalLayout_6 = new QVBoxLayout(tab_console);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        consoleTextEdit = new QPlainTextEdit(tab_console);
        consoleTextEdit->setObjectName(QStringLiteral("consoleTextEdit"));
        consoleTextEdit->setFrameShape(QFrame::StyledPanel);
        consoleTextEdit->setFrameShadow(QFrame::Raised);
        consoleTextEdit->setOverwriteMode(false);
        consoleTextEdit->setTextInteractionFlags(Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        verticalLayout_6->addWidget(consoleTextEdit);

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
        tab_register = new RegisterView();
        tab_register->setObjectName(QStringLiteral("tab_register"));
        verticalLayout_10 = new QVBoxLayout(tab_register);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        widget_3 = new QWidget(tab_register);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        horizontalLayout_4 = new QHBoxLayout(widget_3);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_2 = new QLabel(widget_3);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_4->addWidget(label_2);

        comboBox = new QComboBox(widget_3);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        horizontalLayout_4->addWidget(comboBox);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);


        verticalLayout_10->addWidget(widget_3);

        tableWidget_6 = new QTableWidget(tab_register);
        if (tableWidget_6->columnCount() < 20)
            tableWidget_6->setColumnCount(20);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_6->setHorizontalHeaderItem(0, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget_6->setHorizontalHeaderItem(1, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget_6->setHorizontalHeaderItem(2, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget_6->setHorizontalHeaderItem(3, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget_6->setHorizontalHeaderItem(4, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget_6->setHorizontalHeaderItem(5, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget_6->setHorizontalHeaderItem(6, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget_6->setHorizontalHeaderItem(7, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget_6->setHorizontalHeaderItem(8, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget_6->setHorizontalHeaderItem(9, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidget_6->setHorizontalHeaderItem(10, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidget_6->setHorizontalHeaderItem(11, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableWidget_6->setHorizontalHeaderItem(12, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tableWidget_6->setHorizontalHeaderItem(13, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tableWidget_6->setHorizontalHeaderItem(14, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tableWidget_6->setHorizontalHeaderItem(15, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tableWidget_6->setHorizontalHeaderItem(16, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        tableWidget_6->setHorizontalHeaderItem(17, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        tableWidget_6->setHorizontalHeaderItem(18, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        tableWidget_6->setHorizontalHeaderItem(19, __qtablewidgetitem24);
        tableWidget_6->setObjectName(QStringLiteral("tableWidget_6"));
        tableWidget_6->setFrameShape(QFrame::NoFrame);
        tableWidget_6->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget_6->horizontalHeader()->setCascadingSectionResizes(true);
        tableWidget_6->horizontalHeader()->setStretchLastSection(true);
        tableWidget_6->verticalHeader()->setVisible(false);

        verticalLayout_10->addWidget(tableWidget_6);

        tabWidget_memory->addTab(tab_register, QString());
        tab_cache = new CacheView();
        tab_cache->setObjectName(QStringLiteral("tab_cache"));
        verticalLayout_9 = new QVBoxLayout(tab_cache);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        widget_4 = new QWidget(tab_cache);
        widget_4->setObjectName(QStringLiteral("widget_4"));
        horizontalLayout_5 = new QHBoxLayout(widget_4);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_4 = new QLabel(widget_4);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_5->addWidget(label_4);

        cacheListBox = new QComboBox(widget_4);
        cacheListBox->setObjectName(QStringLiteral("cacheListBox"));

        horizontalLayout_5->addWidget(cacheListBox);

        tagLine = new QLineEdit(widget_4);
        tagLine->setObjectName(QStringLiteral("tagLine"));

        horizontalLayout_5->addWidget(tagLine);

        indexLine = new QLineEdit(widget_4);
        indexLine->setObjectName(QStringLiteral("indexLine"));

        horizontalLayout_5->addWidget(indexLine);

        offsetLine = new QLineEdit(widget_4);
        offsetLine->setObjectName(QStringLiteral("offsetLine"));

        horizontalLayout_5->addWidget(offsetLine);

        pushButton_2 = new QPushButton(widget_4);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_5->addWidget(pushButton_2);

        horizontalLayout_5->setStretch(0, 1);
        horizontalLayout_5->setStretch(1, 8);
        horizontalLayout_5->setStretch(2, 5);
        horizontalLayout_5->setStretch(3, 5);
        horizontalLayout_5->setStretch(4, 5);
        horizontalLayout_5->setStretch(5, 2);

        verticalLayout_9->addWidget(widget_4);

        tableWidget_7 = new QTableWidget(tab_cache);
        if (tableWidget_7->columnCount() < 7)
            tableWidget_7->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        tableWidget_7->setHorizontalHeaderItem(0, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        tableWidget_7->setHorizontalHeaderItem(1, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        tableWidget_7->setHorizontalHeaderItem(2, __qtablewidgetitem27);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        tableWidget_7->setHorizontalHeaderItem(3, __qtablewidgetitem28);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        tableWidget_7->setHorizontalHeaderItem(4, __qtablewidgetitem29);
        QTableWidgetItem *__qtablewidgetitem30 = new QTableWidgetItem();
        tableWidget_7->setHorizontalHeaderItem(5, __qtablewidgetitem30);
        QTableWidgetItem *__qtablewidgetitem31 = new QTableWidgetItem();
        tableWidget_7->setHorizontalHeaderItem(6, __qtablewidgetitem31);
        tableWidget_7->setObjectName(QStringLiteral("tableWidget_7"));
        tableWidget_7->setFrameShape(QFrame::NoFrame);
        tableWidget_7->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget_7->horizontalHeader()->setCascadingSectionResizes(true);
        tableWidget_7->horizontalHeader()->setDefaultSectionSize(150);
        tableWidget_7->horizontalHeader()->setStretchLastSection(true);
        tableWidget_7->verticalHeader()->setVisible(false);

        verticalLayout_9->addWidget(tableWidget_7);

        widget_5 = new QWidget(tab_cache);
        widget_5->setObjectName(QStringLiteral("widget_5"));
        horizontalLayout_6 = new QHBoxLayout(widget_5);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        prevButton = new QPushButton(widget_5);
        prevButton->setObjectName(QStringLiteral("prevButton"));

        horizontalLayout_6->addWidget(prevButton);

        nextButton = new QPushButton(widget_5);
        nextButton->setObjectName(QStringLiteral("nextButton"));

        horizontalLayout_6->addWidget(nextButton);


        verticalLayout_9->addWidget(widget_5);

        tabWidget_memory->addTab(tab_cache, QString());
        tab_memory = new MemoryView();
        tab_memory->setObjectName(QStringLiteral("tab_memory"));
        verticalLayout_7 = new QVBoxLayout(tab_memory);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        widget_2 = new QWidget(tab_memory);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        horizontalLayout_3 = new QHBoxLayout(widget_2);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label = new QLabel(widget_2);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_3->addWidget(label);

        label_3 = new QLabel(widget_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);

        spinBox = new HexSpinBox(widget_2);
        spinBox->setObjectName(QStringLiteral("spinBox"));

        horizontalLayout_3->addWidget(spinBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        lineEdit = new QLineEdit(widget_2);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout_3->addWidget(lineEdit);

        pushButton = new QPushButton(widget_2);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout_3->addWidget(pushButton);


        verticalLayout_7->addWidget(widget_2);

        tableWidget_memory = new QTableWidget(tab_memory);
        if (tableWidget_memory->columnCount() < 4)
            tableWidget_memory->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem32 = new QTableWidgetItem();
        tableWidget_memory->setHorizontalHeaderItem(0, __qtablewidgetitem32);
        QTableWidgetItem *__qtablewidgetitem33 = new QTableWidgetItem();
        tableWidget_memory->setHorizontalHeaderItem(1, __qtablewidgetitem33);
        QTableWidgetItem *__qtablewidgetitem34 = new QTableWidgetItem();
        tableWidget_memory->setHorizontalHeaderItem(2, __qtablewidgetitem34);
        QTableWidgetItem *__qtablewidgetitem35 = new QTableWidgetItem();
        tableWidget_memory->setHorizontalHeaderItem(3, __qtablewidgetitem35);
        tableWidget_memory->setObjectName(QStringLiteral("tableWidget_memory"));
        tableWidget_memory->setFrameShape(QFrame::NoFrame);
        tableWidget_memory->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget_memory->setRowCount(0);
        tableWidget_memory->horizontalHeader()->setDefaultSectionSize(120);
        tableWidget_memory->horizontalHeader()->setStretchLastSection(true);
        tableWidget_memory->verticalHeader()->setVisible(false);

        verticalLayout_7->addWidget(tableWidget_memory);

        tabWidget_memory->addTab(tab_memory, QString());

        verticalLayout->addWidget(tabWidget_memory);

        widget = new QWidget(centralwidget);
        widget->setObjectName(QStringLiteral("widget"));

        verticalLayout->addWidget(widget);

        verticalLayout->setStretch(0, 3);
        verticalLayout->setStretch(1, 6);

        horizontalLayout->addLayout(verticalLayout);

        horizontalLayout->setStretch(0, 8);
        horizontalLayout->setStretch(1, 5);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1920, 27));
        QFont font;
        font.setFamily(QStringLiteral("Hack"));
        menubar->setFont(font);
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
        menuSettings = new QMenu(menubar);
        menuSettings->setObjectName(QStringLiteral("menuSettings"));
        MainWindow->setMenuBar(menubar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);
        QWidget::setTabOrder(tabWidget_pipeline, tabWidget_memory);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuEdt->menuAction());
        menubar->addAction(menuWindow->menuAction());
        menubar->addAction(menuSettings->menuAction());
        menubar->addAction(menuWindow_2->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionnew);
        menuFile->addAction(actionopen);
        menuFile->addSeparator();
        menuFile->addAction(actionsave);
        menuFile->addAction(actionSave_As);
        menuFile->addAction(actionSave_all);
        menuFile->addSeparator();
        menuFile->addAction(actionSave_state);
        menuFile->addAction(actionRestore_State);
        menuEdt->addAction(actionUndo);
        menuEdt->addAction(actionRedo);
        menuEdt->addSeparator();
        menuEdt->addAction(actionCut);
        menuEdt->addAction(actionCopy);
        menuEdt->addAction(actionPaste);
        menuEdt->addAction(actionDelete);
        menuWindow->addAction(actionRun);
        menuWindow->addAction(actionstop);
        menuWindow->addAction(actionpause);
        menuWindow->addSeparator();
        menuWindow->addAction(actionbuild);
        menuWindow->addAction(actionbuild_all);
        menuWindow_2->addAction(menu_Cache->menuAction());
        menuWindow_2->addAction(actionPipeline);
        menu_Cache->addAction(actionPredefined);
        menu_Cache->addSeparator();
        menu_Cache->addAction(actionAddCache);
        menu_Cache->addAction(actionRemoveCache);
        menu_Cache->addAction(actionClearCache);
        menuHelp->addAction(actionPISA_Help);
        menuHelp->addAction(actionAbout_PISA);
        menuSettings->addAction(actionPreference);
        toolBar->addAction(actionnew);
        toolBar->addAction(actionopen);
        toolBar->addAction(actionsave);
        toolBar->addAction(actionSave_all);
        toolBar->addSeparator();
        toolBar->addAction(actionbuild);
        toolBar->addAction(actionbuild_all);
        toolBar->addAction(actionUpload);
        toolBar->addSeparator();
        toolBar->addAction(actionRun);
        toolBar->addAction(actionpause);
        toolBar->addAction(actionstop);
        toolBar->addSeparator();
        toolBar->addAction(actionrewind);
        toolBar->addAction(actionforward);
        toolBar->addSeparator();

        retranslateUi(MainWindow);
        QObject::connect(actionnew, SIGNAL(triggered()), MainWindow, SLOT(handleNew()));
        QObject::connect(actionopen, SIGNAL(triggered()), MainWindow, SLOT(handleOpen()));
        QObject::connect(actionsave, SIGNAL(triggered()), MainWindow, SLOT(handleSave()));
        QObject::connect(actionRedo, SIGNAL(triggered()), MainWindow, SLOT(handleRedo()));
        QObject::connect(actionUndo, SIGNAL(triggered()), MainWindow, SLOT(handleUndo()));
        QObject::connect(actionSave_As, SIGNAL(triggered()), MainWindow, SLOT(handleSaveAs()));
        QObject::connect(actionAbout_PISA, SIGNAL(triggered()), MainWindow, SLOT(handleAboutPISA()));
        QObject::connect(actionAddCache, SIGNAL(triggered()), MainWindow, SLOT(handleAddCache()));
        QObject::connect(actionClearCache, SIGNAL(triggered()), MainWindow, SLOT(handleClearCache()));
        QObject::connect(actionRemoveCache, SIGNAL(triggered()), MainWindow, SLOT(handleRemoveCache()));
        QObject::connect(editorTab, SIGNAL(tabCloseRequested(int)), editorTab, SLOT(closeTab(int)));
        QObject::connect(actionPreference, SIGNAL(triggered()), MainWindow, SLOT(handlePreference()));
        QObject::connect(actionbuild, SIGNAL(triggered()), MainWindow, SLOT(handleBuild()));
        QObject::connect(actionbuild_all, SIGNAL(triggered()), MainWindow, SLOT(handleBuildAll()));
        QObject::connect(actionSave_all, SIGNAL(triggered()), MainWindow, SLOT(handleSaveAll()));
        QObject::connect(actionRun, SIGNAL(triggered()), MainWindow, SLOT(handlePlay()));
        QObject::connect(actionpause, SIGNAL(triggered()), MainWindow, SLOT(handlePause()));
        QObject::connect(actionrewind, SIGNAL(triggered()), MainWindow, SLOT(handleBackward()));
        QObject::connect(actionstop, SIGNAL(triggered()), MainWindow, SLOT(handleStop()));
        QObject::connect(actionforward, SIGNAL(triggered()), MainWindow, SLOT(handleForward()));
        QObject::connect(fileSystemView, SIGNAL(doubleClicked(QModelIndex)), MainWindow, SLOT(handleOpenFromNavigation(QModelIndex)));
        QObject::connect(tracker, SIGNAL(customContextMenuRequested(QPoint)), tracker, SLOT(customContextMenu(QPoint)));
        QObject::connect(actionUpload, SIGNAL(triggered()), MainWindow, SLOT(handleUpload()));
        QObject::connect(tabWidget_memory, SIGNAL(currentChanged(int)), MainWindow, SLOT(updateMemoryWidget()));
        QObject::connect(actionRestore_State, SIGNAL(triggered()), MainWindow, SLOT(handleRestoreState()));
        QObject::connect(actionSave_state, SIGNAL(triggered()), MainWindow, SLOT(handleSaveState()));

        leftBoard->setCurrentIndex(1);
        editorTab->setCurrentIndex(-1);
        tabWidget_output->setCurrentIndex(1);
        tabWidget_pipeline->setCurrentIndex(0);
        tabWidget_memory->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "PISA", Q_NULLPTR));
        actionSave_As->setText(QApplication::translate("MainWindow", "Sa&ve As", Q_NULLPTR));
        actionPipeline->setText(QApplication::translate("MainWindow", "&Pipeline", Q_NULLPTR));
        actionRun->setText(QApplication::translate("MainWindow", "&Run", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionRun->setToolTip(QApplication::translate("MainWindow", "Run Program", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionAbout_PISA->setText(QApplication::translate("MainWindow", "&About PISA", Q_NULLPTR));
        actionPISA_Help->setText(QApplication::translate("MainWindow", "&PISA Help", Q_NULLPTR));
        actionnew->setText(QApplication::translate("MainWindow", "&New", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionnew->setToolTip(QApplication::translate("MainWindow", "Create New File", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionnew->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", Q_NULLPTR));
        actionopen->setText(QApplication::translate("MainWindow", "&open", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionopen->setToolTip(QApplication::translate("MainWindow", "Open File", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionopen->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+N", Q_NULLPTR));
        actionsave->setText(QApplication::translate("MainWindow", "&Save", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionsave->setToolTip(QApplication::translate("MainWindow", "Save File", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionsave->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", Q_NULLPTR));
        actionstop->setText(QApplication::translate("MainWindow", "&stop", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionstop->setToolTip(QApplication::translate("MainWindow", "Stop Program", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionpause->setText(QApplication::translate("MainWindow", "&pause", Q_NULLPTR));
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
        actionbuild->setText(QApplication::translate("MainWindow", "&build", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionbuild->setToolTip(QApplication::translate("MainWindow", "Build Current File", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionbuild_all->setText(QApplication::translate("MainWindow", "b&uild all", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionbuild_all->setToolTip(QApplication::translate("MainWindow", "Build All Files", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionUndo->setText(QApplication::translate("MainWindow", "&Undo", Q_NULLPTR));
        actionUndo->setShortcut(QApplication::translate("MainWindow", "Ctrl+Z", Q_NULLPTR));
        actionRedo->setText(QApplication::translate("MainWindow", "&Redo", Q_NULLPTR));
        actionRedo->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+Z", Q_NULLPTR));
        actionCut->setText(QApplication::translate("MainWindow", "&Cut", Q_NULLPTR));
        actionCut->setShortcut(QApplication::translate("MainWindow", "Ctrl+X", Q_NULLPTR));
        actionCopy->setText(QApplication::translate("MainWindow", "C&opy", Q_NULLPTR));
        actionCopy->setShortcut(QApplication::translate("MainWindow", "Ctrl+C", Q_NULLPTR));
        actionPaste->setText(QApplication::translate("MainWindow", "&Paste", Q_NULLPTR));
        actionPaste->setShortcut(QApplication::translate("MainWindow", "Ctrl+V", Q_NULLPTR));
        actionDelete->setText(QApplication::translate("MainWindow", "&Delete", Q_NULLPTR));
        actionDelete->setShortcut(QApplication::translate("MainWindow", "Ctrl+D", Q_NULLPTR));
        actionSave_state->setText(QApplication::translate("MainWindow", "&Save State", Q_NULLPTR));
        actionRestore_State->setText(QApplication::translate("MainWindow", "&Restore State", Q_NULLPTR));
        actionAddCache->setText(QApplication::translate("MainWindow", "&Add Cache", Q_NULLPTR));
        actionRemoveCache->setText(QApplication::translate("MainWindow", "&Remove Cache", Q_NULLPTR));
        actionClearCache->setText(QApplication::translate("MainWindow", "&Clear Cache", Q_NULLPTR));
        actionPredefined->setText(QApplication::translate("MainWindow", "&Predefined", Q_NULLPTR));
        actionPreference->setText(QApplication::translate("MainWindow", "&Preference...", Q_NULLPTR));
        actionSave_all->setText(QApplication::translate("MainWindow", "Sav&e_all", Q_NULLPTR));
        actionSave_all->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+S", Q_NULLPTR));
        actionUpload->setText(QApplication::translate("MainWindow", "Upload", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionUpload->setToolTip(QApplication::translate("MainWindow", "Upload file", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        leftBoard->setTabText(leftBoard->indexOf(tab_navigation), QApplication::translate("MainWindow", "Navigation", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("MainWindow", "Performance", Q_NULLPTR));
        leftBoard->setTabText(leftBoard->indexOf(tab_performance), QApplication::translate("MainWindow", "Performance", Q_NULLPTR));
        leftBoard->setTabText(leftBoard->indexOf(Track), QApplication::translate("MainWindow", "Tracker", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = problemTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "Type", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = problemTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "File", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = problemTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "Line", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = problemTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "Word", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = problemTable->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("MainWindow", "Description", Q_NULLPTR));
        tabWidget_output->setTabText(tabWidget_output->indexOf(tab_problems), QApplication::translate("MainWindow", "Problems", Q_NULLPTR));
        tabWidget_output->setTabText(tabWidget_output->indexOf(tab_console), QApplication::translate("MainWindow", "Console", Q_NULLPTR));
        tabWidget_output->setTabText(tabWidget_output->indexOf(tab_screen), QApplication::translate("MainWindow", "Screen", Q_NULLPTR));
        tabWidget_pipeline->setTabText(tabWidget_pipeline->indexOf(tab_scalar), QApplication::translate("MainWindow", "Scalar", Q_NULLPTR));
        tabWidget_pipeline->setTabText(tabWidget_pipeline->indexOf(tab_vector), QApplication::translate("MainWindow", "Vector", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Type:", Q_NULLPTR));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "General Registers", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Integer Vector #0", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Integer Vector #1", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Integer Vector #2", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Integer Vector #3", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Float Vector #0", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Float Vector #1", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Float Vector #2", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Float Vector #3", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Flag Registers", Q_NULLPTR)
        );
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_6->horizontalHeaderItem(0);
        ___qtablewidgetitem5->setText(QApplication::translate("MainWindow", "Address", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget_6->horizontalHeaderItem(1);
        ___qtablewidgetitem6->setText(QApplication::translate("MainWindow", "Hex", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget_6->horizontalHeaderItem(2);
        ___qtablewidgetitem7->setText(QApplication::translate("MainWindow", "Decimal", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget_6->horizontalHeaderItem(3);
        ___qtablewidgetitem8->setText(QApplication::translate("MainWindow", "Binary", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget_6->horizontalHeaderItem(4);
        ___qtablewidgetitem9->setText(QApplication::translate("MainWindow", "EQ", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget_6->horizontalHeaderItem(5);
        ___qtablewidgetitem10->setText(QApplication::translate("MainWindow", "NE", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget_6->horizontalHeaderItem(6);
        ___qtablewidgetitem11->setText(QApplication::translate("MainWindow", "CS", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget_6->horizontalHeaderItem(7);
        ___qtablewidgetitem12->setText(QApplication::translate("MainWindow", "CC", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget_6->horizontalHeaderItem(8);
        ___qtablewidgetitem13->setText(QApplication::translate("MainWindow", "MI", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget_6->horizontalHeaderItem(9);
        ___qtablewidgetitem14->setText(QApplication::translate("MainWindow", "PL", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidget_6->horizontalHeaderItem(10);
        ___qtablewidgetitem15->setText(QApplication::translate("MainWindow", "VS", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidget_6->horizontalHeaderItem(11);
        ___qtablewidgetitem16->setText(QApplication::translate("MainWindow", "VC", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidget_6->horizontalHeaderItem(12);
        ___qtablewidgetitem17->setText(QApplication::translate("MainWindow", "DZ", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem18 = tableWidget_6->horizontalHeaderItem(13);
        ___qtablewidgetitem18->setText(QApplication::translate("MainWindow", "NZ", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem19 = tableWidget_6->horizontalHeaderItem(14);
        ___qtablewidgetitem19->setText(QApplication::translate("MainWindow", "LE", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem20 = tableWidget_6->horizontalHeaderItem(15);
        ___qtablewidgetitem20->setText(QApplication::translate("MainWindow", "GE", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem21 = tableWidget_6->horizontalHeaderItem(16);
        ___qtablewidgetitem21->setText(QApplication::translate("MainWindow", "LT", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem22 = tableWidget_6->horizontalHeaderItem(17);
        ___qtablewidgetitem22->setText(QApplication::translate("MainWindow", "GT", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem23 = tableWidget_6->horizontalHeaderItem(18);
        ___qtablewidgetitem23->setText(QApplication::translate("MainWindow", "AL", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem24 = tableWidget_6->horizontalHeaderItem(19);
        ___qtablewidgetitem24->setText(QApplication::translate("MainWindow", "UN", Q_NULLPTR));
        tabWidget_memory->setTabText(tabWidget_memory->indexOf(tab_register), QApplication::translate("MainWindow", "Register", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "Type:", Q_NULLPTR));
        tagLine->setInputMask(QString());
        tagLine->setPlaceholderText(QApplication::translate("MainWindow", "Tag", Q_NULLPTR));
        indexLine->setPlaceholderText(QApplication::translate("MainWindow", "Index", Q_NULLPTR));
        offsetLine->setPlaceholderText(QApplication::translate("MainWindow", "Offset", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("MainWindow", "Search", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem25 = tableWidget_7->horizontalHeaderItem(0);
        ___qtablewidgetitem25->setText(QApplication::translate("MainWindow", "V", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem26 = tableWidget_7->horizontalHeaderItem(1);
        ___qtablewidgetitem26->setText(QApplication::translate("MainWindow", "D", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem27 = tableWidget_7->horizontalHeaderItem(2);
        ___qtablewidgetitem27->setText(QApplication::translate("MainWindow", "LRU", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem28 = tableWidget_7->horizontalHeaderItem(3);
        ___qtablewidgetitem28->setText(QApplication::translate("MainWindow", "Tag", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem29 = tableWidget_7->horizontalHeaderItem(4);
        ___qtablewidgetitem29->setText(QApplication::translate("MainWindow", "Index", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem30 = tableWidget_7->horizontalHeaderItem(5);
        ___qtablewidgetitem30->setText(QApplication::translate("MainWindow", "Offset", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem31 = tableWidget_7->horizontalHeaderItem(6);
        ___qtablewidgetitem31->setText(QApplication::translate("MainWindow", "Value", Q_NULLPTR));
        prevButton->setText(QApplication::translate("MainWindow", "<<", Q_NULLPTR));
        nextButton->setText(QApplication::translate("MainWindow", ">>", Q_NULLPTR));
        tabWidget_memory->setTabText(tabWidget_memory->indexOf(tab_cache), QApplication::translate("MainWindow", "Cache", Q_NULLPTR));
        label->setText(QString());
        label_3->setText(QApplication::translate("MainWindow", "Address: ", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "Search", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem32 = tableWidget_memory->horizontalHeaderItem(0);
        ___qtablewidgetitem32->setText(QApplication::translate("MainWindow", "Address", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem33 = tableWidget_memory->horizontalHeaderItem(1);
        ___qtablewidgetitem33->setText(QApplication::translate("MainWindow", "Hex", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem34 = tableWidget_memory->horizontalHeaderItem(2);
        ___qtablewidgetitem34->setText(QApplication::translate("MainWindow", "Decimal", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem35 = tableWidget_memory->horizontalHeaderItem(3);
        ___qtablewidgetitem35->setText(QApplication::translate("MainWindow", "Binary", Q_NULLPTR));
        tabWidget_memory->setTabText(tabWidget_memory->indexOf(tab_memory), QApplication::translate("MainWindow", "Memory", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("MainWindow", "Fi&le", Q_NULLPTR));
        menuEdt->setTitle(QApplication::translate("MainWindow", "E&dt", Q_NULLPTR));
        menuWindow->setTitle(QApplication::translate("MainWindow", "&Run", Q_NULLPTR));
        menuWindow_2->setTitle(QApplication::translate("MainWindow", "Mod&ule", Q_NULLPTR));
        menu_Cache->setTitle(QApplication::translate("MainWindow", "&Cache", Q_NULLPTR));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", Q_NULLPTR));
        menuSettings->setTitle(QApplication::translate("MainWindow", "Setti&ngs", Q_NULLPTR));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PISA_H
