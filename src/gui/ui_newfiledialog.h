/********************************************************************************
** Form generated from reading UI file 'newfiledialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWFILEDIALOG_H
#define UI_NEWFILEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_NewFileDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *lineEdit_directory;
    QPushButton *openButton;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit_fileName;
    QPushButton *randomButton;

    void setupUi(QDialog *NewFileDialog)
    {
        if (NewFileDialog->objectName().isEmpty())
            NewFileDialog->setObjectName(QStringLiteral("NewFileDialog"));
        NewFileDialog->resize(393, 223);
        buttonBox = new QDialogButtonBox(NewFileDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 170, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        lineEdit_directory = new QLineEdit(NewFileDialog);
        lineEdit_directory->setObjectName(QStringLiteral("lineEdit_directory"));
        lineEdit_directory->setGeometry(QRect(0, 30, 311, 29));
        lineEdit_directory->setReadOnly(true);
        openButton = new QPushButton(NewFileDialog);
        openButton->setObjectName(QStringLiteral("openButton"));
        openButton->setGeometry(QRect(320, 30, 71, 31));
        label = new QLabel(NewFileDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 81, 16));
        label_2 = new QLabel(NewFileDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 70, 81, 16));
        lineEdit_fileName = new QLineEdit(NewFileDialog);
        lineEdit_fileName->setObjectName(QStringLiteral("lineEdit_fileName"));
        lineEdit_fileName->setGeometry(QRect(0, 90, 311, 29));
        randomButton = new QPushButton(NewFileDialog);
        randomButton->setObjectName(QStringLiteral("randomButton"));
        randomButton->setGeometry(QRect(320, 90, 71, 31));

        retranslateUi(NewFileDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), NewFileDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), NewFileDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(NewFileDialog);
    } // setupUi

    void retranslateUi(QDialog *NewFileDialog)
    {
        NewFileDialog->setWindowTitle(QApplication::translate("NewFileDialog", "New File", Q_NULLPTR));
        openButton->setText(QApplication::translate("NewFileDialog", "Open", Q_NULLPTR));
        label->setText(QApplication::translate("NewFileDialog", "Directory:", Q_NULLPTR));
        label_2->setText(QApplication::translate("NewFileDialog", "File Name:", Q_NULLPTR));
        randomButton->setText(QApplication::translate("NewFileDialog", "Random", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class NewFileDialog: public Ui_NewFileDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWFILEDIALOG_H
