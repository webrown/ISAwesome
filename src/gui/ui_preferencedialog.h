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
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit_WorkDirectory;
    QPushButton *button_open2;
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
    QCheckBox *checkBox_4;
    QCheckBox *checkBox_7;
    QCheckBox *checkBox_5;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_9;
    QCheckBox *checkBox;
    QCheckBox *checkBox_6;
    QCheckBox *checkBox_8;
    QCheckBox *checkBox_3;
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
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        lineEdit_WorkDirectory = new QLineEdit(widget);
        lineEdit_WorkDirectory->setObjectName(QStringLiteral("lineEdit_WorkDirectory"));

        horizontalLayout->addWidget(lineEdit_WorkDirectory);

        button_open2 = new QPushButton(widget);
        button_open2->setObjectName(QStringLiteral("button_open2"));

        horizontalLayout->addWidget(button_open2);


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
        checkBox_4 = new QCheckBox(groupBox);
        checkBox_4->setObjectName(QStringLiteral("checkBox_4"));

        gridLayout_2->addWidget(checkBox_4, 0, 1, 1, 1);

        checkBox_7 = new QCheckBox(groupBox);
        checkBox_7->setObjectName(QStringLiteral("checkBox_7"));

        gridLayout_2->addWidget(checkBox_7, 0, 2, 1, 1);

        checkBox_5 = new QCheckBox(groupBox);
        checkBox_5->setObjectName(QStringLiteral("checkBox_5"));

        gridLayout_2->addWidget(checkBox_5, 2, 0, 1, 1);

        checkBox_2 = new QCheckBox(groupBox);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));

        gridLayout_2->addWidget(checkBox_2, 1, 0, 1, 1);

        checkBox_9 = new QCheckBox(groupBox);
        checkBox_9->setObjectName(QStringLiteral("checkBox_9"));

        gridLayout_2->addWidget(checkBox_9, 2, 2, 1, 1);

        checkBox = new QCheckBox(groupBox);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        gridLayout_2->addWidget(checkBox, 0, 0, 1, 1);

        checkBox_6 = new QCheckBox(groupBox);
        checkBox_6->setObjectName(QStringLiteral("checkBox_6"));

        gridLayout_2->addWidget(checkBox_6, 2, 1, 1, 1);

        checkBox_8 = new QCheckBox(groupBox);
        checkBox_8->setObjectName(QStringLiteral("checkBox_8"));

        gridLayout_2->addWidget(checkBox_8, 1, 2, 1, 1);

        checkBox_3 = new QCheckBox(groupBox);
        checkBox_3->setObjectName(QStringLiteral("checkBox_3"));

        gridLayout_2->addWidget(checkBox_3, 1, 1, 1, 1);


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
        button_open2->setText(QApplication::translate("PreferenceDialog", "Open...", Q_NULLPTR));
        label_4->setText(QApplication::translate("PreferenceDialog", "Font:", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_general), QApplication::translate("PreferenceDialog", "General", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("PreferenceDialog", "Misc. Setting", Q_NULLPTR));
        checkBox_4->setText(QApplication::translate("PreferenceDialog", "Global Macro", Q_NULLPTR));
        checkBox_7->setText(QApplication::translate("PreferenceDialog", "Wall", Q_NULLPTR));
        checkBox_5->setText(QApplication::translate("PreferenceDialog", "Something", Q_NULLPTR));
        checkBox_2->setText(QApplication::translate("PreferenceDialog", "Use Default Alias", Q_NULLPTR));
        checkBox_9->setText(QApplication::translate("PreferenceDialog", "Somthing", Q_NULLPTR));
        checkBox->setText(QApplication::translate("PreferenceDialog", "Use Default Macro", Q_NULLPTR));
        checkBox_6->setText(QApplication::translate("PreferenceDialog", "Main Entry", Q_NULLPTR));
        checkBox_8->setText(QApplication::translate("PreferenceDialog", "Preserve Comment", Q_NULLPTR));
        checkBox_3->setText(QApplication::translate("PreferenceDialog", "Global Alias", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_assembly), QApplication::translate("PreferenceDialog", "Assembly", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("PreferenceDialog", "Disassembly", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PreferenceDialog: public Ui_PreferenceDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREFERENCEDIALOG_H
