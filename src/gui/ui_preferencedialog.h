/********************************************************************************
** Form generated from reading UI file 'preferencedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREFERENCEDIALOG_H
#define UI_PREFERENCEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFontComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PreferenceDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidget;
    QWidget *tab_general;
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *lineEdit_WorkDirectory;
    QPushButton *button_open2;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QFontComboBox *fontComboBox;
    QSpinBox *spinBox;
    QWidget *tab_assembly;
    QVBoxLayout *verticalLayout_7;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QCheckBox *globalMacroCheckBox;
    QCheckBox *wallCheckBox;
    QCheckBox *somethingCheckBox1;
    QCheckBox *defaultAliasCheckBox;
    QCheckBox *seomthingCheckBox2;
    QCheckBox *defaultMacroCheckBox;
    QCheckBox *mainEntryCheckBox;
    QCheckBox *preserveCommetnCheckBox;
    QCheckBox *globalAliasCheckBox;
    QWidget *tab;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *PreferenceDialog)
    {
        if (PreferenceDialog->objectName().isEmpty())
            PreferenceDialog->setObjectName(QStringLiteral("PreferenceDialog"));
        PreferenceDialog->resize(700, 596);
        verticalLayout_2 = new QVBoxLayout(PreferenceDialog);
        verticalLayout_2->setSpacing(3);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(3, 3, -1, 3);
        tabWidget = new QTabWidget(PreferenceDialog);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setTabPosition(QTabWidget::North);
        tab_general = new QWidget();
        tab_general->setObjectName(QStringLiteral("tab_general"));
        verticalLayout = new QVBoxLayout(tab_general);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        widget = new QWidget(tab_general);
        widget->setObjectName(QStringLiteral("widget"));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        lineEdit_WorkDirectory = new QLineEdit(widget);
        lineEdit_WorkDirectory->setObjectName(QStringLiteral("lineEdit_WorkDirectory"));

        gridLayout->addWidget(lineEdit_WorkDirectory, 0, 1, 1, 1);

        button_open2 = new QPushButton(widget);
        button_open2->setObjectName(QStringLiteral("button_open2"));

        gridLayout->addWidget(button_open2, 0, 2, 1, 1);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        gridLayout->addWidget(lineEdit, 2, 1, 1, 1);

        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 2, 2, 1, 1);


        verticalLayout->addWidget(widget);

        widget_4 = new QWidget(tab_general);
        widget_4->setObjectName(QStringLiteral("widget_4"));
        horizontalLayout_3 = new QHBoxLayout(widget_4);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_4 = new QLabel(widget_4);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_3->addWidget(label_4);

        fontComboBox = new QFontComboBox(widget_4);
        fontComboBox->setObjectName(QStringLiteral("fontComboBox"));

        horizontalLayout_3->addWidget(fontComboBox);

        spinBox = new QSpinBox(widget_4);
        spinBox->setObjectName(QStringLiteral("spinBox"));

        horizontalLayout_3->addWidget(spinBox);


        verticalLayout->addWidget(widget_4);

        tabWidget->addTab(tab_general, QString());
        tab_assembly = new QWidget();
        tab_assembly->setObjectName(QStringLiteral("tab_assembly"));
        verticalLayout_7 = new QVBoxLayout(tab_assembly);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        widget_2 = new QWidget(tab_assembly);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));

        verticalLayout_7->addWidget(widget_2);

        groupBox = new QGroupBox(tab_assembly);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        globalMacroCheckBox = new QCheckBox(groupBox);
        globalMacroCheckBox->setObjectName(QStringLiteral("globalMacroCheckBox"));

        gridLayout_2->addWidget(globalMacroCheckBox, 0, 1, 1, 1);

        wallCheckBox = new QCheckBox(groupBox);
        wallCheckBox->setObjectName(QStringLiteral("wallCheckBox"));

        gridLayout_2->addWidget(wallCheckBox, 0, 2, 1, 1);

        somethingCheckBox1 = new QCheckBox(groupBox);
        somethingCheckBox1->setObjectName(QStringLiteral("somethingCheckBox1"));

        gridLayout_2->addWidget(somethingCheckBox1, 2, 0, 1, 1);

        defaultAliasCheckBox = new QCheckBox(groupBox);
        defaultAliasCheckBox->setObjectName(QStringLiteral("defaultAliasCheckBox"));

        gridLayout_2->addWidget(defaultAliasCheckBox, 1, 0, 1, 1);

        seomthingCheckBox2 = new QCheckBox(groupBox);
        seomthingCheckBox2->setObjectName(QStringLiteral("seomthingCheckBox2"));

        gridLayout_2->addWidget(seomthingCheckBox2, 2, 2, 1, 1);

        defaultMacroCheckBox = new QCheckBox(groupBox);
        defaultMacroCheckBox->setObjectName(QStringLiteral("defaultMacroCheckBox"));

        gridLayout_2->addWidget(defaultMacroCheckBox, 0, 0, 1, 1);

        mainEntryCheckBox = new QCheckBox(groupBox);
        mainEntryCheckBox->setObjectName(QStringLiteral("mainEntryCheckBox"));

        gridLayout_2->addWidget(mainEntryCheckBox, 2, 1, 1, 1);

        preserveCommetnCheckBox = new QCheckBox(groupBox);
        preserveCommetnCheckBox->setObjectName(QStringLiteral("preserveCommetnCheckBox"));

        gridLayout_2->addWidget(preserveCommetnCheckBox, 1, 2, 1, 1);

        globalAliasCheckBox = new QCheckBox(groupBox);
        globalAliasCheckBox->setObjectName(QStringLiteral("globalAliasCheckBox"));

        gridLayout_2->addWidget(globalAliasCheckBox, 1, 1, 1, 1);


        verticalLayout_7->addWidget(groupBox);

        tabWidget->addTab(tab_assembly, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        tabWidget->addTab(tab, QString());

        verticalLayout_2->addWidget(tabWidget);

        buttonBox = new QDialogButtonBox(PreferenceDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_2->addWidget(buttonBox);


        retranslateUi(PreferenceDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), PreferenceDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), PreferenceDialog, SLOT(reject()));
        QObject::connect(button_open2, SIGNAL(clicked()), PreferenceDialog, SLOT(handleOpen_WorkDirectory()));

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(PreferenceDialog);
    } // setupUi

    void retranslateUi(QDialog *PreferenceDialog)
    {
        PreferenceDialog->setWindowTitle(QApplication::translate("PreferenceDialog", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("PreferenceDialog", "Work Directory:", Q_NULLPTR));
        button_open2->setText(QApplication::translate("PreferenceDialog", "Open", Q_NULLPTR));
        label_2->setText(QApplication::translate("PreferenceDialog", "Ouput Extension: ", Q_NULLPTR));
        pushButton->setText(QApplication::translate("PreferenceDialog", "Default", Q_NULLPTR));
        label_4->setText(QApplication::translate("PreferenceDialog", "Font:", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_general), QApplication::translate("PreferenceDialog", "General", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("PreferenceDialog", "Misc. Setting", Q_NULLPTR));
        globalMacroCheckBox->setText(QApplication::translate("PreferenceDialog", "Global Macro", Q_NULLPTR));
        wallCheckBox->setText(QApplication::translate("PreferenceDialog", "Wall", Q_NULLPTR));
        somethingCheckBox1->setText(QApplication::translate("PreferenceDialog", "Something", Q_NULLPTR));
        defaultAliasCheckBox->setText(QApplication::translate("PreferenceDialog", "Use Default Alias", Q_NULLPTR));
        seomthingCheckBox2->setText(QApplication::translate("PreferenceDialog", "Somthing", Q_NULLPTR));
        defaultMacroCheckBox->setText(QApplication::translate("PreferenceDialog", "Use Default Macro", Q_NULLPTR));
        mainEntryCheckBox->setText(QApplication::translate("PreferenceDialog", "Main Entry", Q_NULLPTR));
        preserveCommetnCheckBox->setText(QApplication::translate("PreferenceDialog", "Preserve Comment", Q_NULLPTR));
        globalAliasCheckBox->setText(QApplication::translate("PreferenceDialog", "Global Alias", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_assembly), QApplication::translate("PreferenceDialog", "Assembly", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("PreferenceDialog", "Simulation", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PreferenceDialog: public Ui_PreferenceDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREFERENCEDIALOG_H
