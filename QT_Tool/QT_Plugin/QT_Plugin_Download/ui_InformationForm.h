/********************************************************************************
** Form generated from reading UI file 'InformationForm.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INFORMATIONFORM_H
#define UI_INFORMATIONFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InformationForm
{
public:
    QPlainTextEdit *plainTextEdit;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;

    void setupUi(QWidget *InformationForm)
    {
        if (InformationForm->objectName().isEmpty())
            InformationForm->setObjectName(QString::fromUtf8("InformationForm"));
        InformationForm->resize(400, 300);
        plainTextEdit = new QPlainTextEdit(InformationForm);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(20, 10, 351, 81));
        label = new QLabel(InformationForm);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(50, 120, 54, 12));
        label_2 = new QLabel(InformationForm);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(190, 120, 54, 12));
        lineEdit = new QLineEdit(InformationForm);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(20, 160, 113, 20));
        lineEdit_2 = new QLineEdit(InformationForm);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(220, 150, 113, 20));

        retranslateUi(InformationForm);

        QMetaObject::connectSlotsByName(InformationForm);
    } // setupUi

    void retranslateUi(QWidget *InformationForm)
    {
        InformationForm->setWindowTitle(QApplication::translate("InformationForm", "Form", nullptr));
        label->setText(QApplication::translate("InformationForm", "TextLabel", nullptr));
        label_2->setText(QApplication::translate("InformationForm", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InformationForm: public Ui_InformationForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INFORMATIONFORM_H
