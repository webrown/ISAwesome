/********************************************************************************
** Form generated from reading UI file 'newcachedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWCACHEDIALOG_H
#define UI_NEWCACHEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_NewCacheDialog
{
public:
    QGridLayout *gridLayout;
    QDoubleSpinBox *delaySpin;
    QDialogButtonBox *buttonBox;
    QComboBox *nextBox;
    QLabel *label_2;
    QSpinBox *offsetSpin;
    QSpinBox *indexSpin;
    QLabel *label_7;
    QComboBox *typeBox;
    QSpinBox *waySpin;
    QLabel *label_4;
    QLabel *label_8;
    QLabel *label_5;
    QLabel *label_3;

    void setupUi(QDialog *NewCacheDialog)
    {
        if (NewCacheDialog->objectName().isEmpty())
            NewCacheDialog->setObjectName(QStringLiteral("NewCacheDialog"));
        NewCacheDialog->setWindowModality(Qt::NonModal);
        NewCacheDialog->resize(350, 350);
        gridLayout = new QGridLayout(NewCacheDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        delaySpin = new QDoubleSpinBox(NewCacheDialog);
        delaySpin->setObjectName(QStringLiteral("delaySpin"));
        delaySpin->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(delaySpin, 5, 1, 1, 1);

        buttonBox = new QDialogButtonBox(NewCacheDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 6, 1, 1, 1);

        nextBox = new QComboBox(NewCacheDialog);
        nextBox->setObjectName(QStringLiteral("nextBox"));

        gridLayout->addWidget(nextBox, 1, 1, 1, 1);

        label_2 = new QLabel(NewCacheDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        offsetSpin = new QSpinBox(NewCacheDialog);
        offsetSpin->setObjectName(QStringLiteral("offsetSpin"));
        offsetSpin->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(offsetSpin, 3, 1, 1, 1);

        indexSpin = new QSpinBox(NewCacheDialog);
        indexSpin->setObjectName(QStringLiteral("indexSpin"));
        indexSpin->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(indexSpin, 2, 1, 1, 1);

        label_7 = new QLabel(NewCacheDialog);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout->addWidget(label_7, 1, 0, 1, 1);

        typeBox = new QComboBox(NewCacheDialog);
        typeBox->setObjectName(QStringLiteral("typeBox"));

        gridLayout->addWidget(typeBox, 0, 1, 1, 1);

        waySpin = new QSpinBox(NewCacheDialog);
        waySpin->setObjectName(QStringLiteral("waySpin"));
        waySpin->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(waySpin, 4, 1, 1, 1);

        label_4 = new QLabel(NewCacheDialog);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 4, 0, 1, 1);

        label_8 = new QLabel(NewCacheDialog);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout->addWidget(label_8, 0, 0, 1, 1);

        label_5 = new QLabel(NewCacheDialog);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 5, 0, 1, 1);

        label_3 = new QLabel(NewCacheDialog);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 3, 0, 1, 1);


        retranslateUi(NewCacheDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), NewCacheDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), NewCacheDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(NewCacheDialog);
    } // setupUi

    void retranslateUi(QDialog *NewCacheDialog)
    {
        NewCacheDialog->setWindowTitle(QApplication::translate("NewCacheDialog", "New Cache", 0));
        label_2->setText(QApplication::translate("NewCacheDialog", "Index Bits:", 0));
        label_7->setText(QApplication::translate("NewCacheDialog", "After:", 0));
        typeBox->clear();
        typeBox->insertItems(0, QStringList()
         << QApplication::translate("NewCacheDialog", "Data & Instruction", 0)
         << QApplication::translate("NewCacheDialog", "Data Only", 0)
         << QApplication::translate("NewCacheDialog", "Instruction Only", 0)
        );
        label_4->setText(QApplication::translate("NewCacheDialog", "Way Bits:", 0));
        label_8->setText(QApplication::translate("NewCacheDialog", "Type:", 0));
        label_5->setText(QApplication::translate("NewCacheDialog", "Delay Bits:", 0));
        label_3->setText(QApplication::translate("NewCacheDialog", "Offset Bits:", 0));
    } // retranslateUi

};

namespace Ui {
    class NewCacheDialog: public Ui_NewCacheDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWCACHEDIALOG_H
