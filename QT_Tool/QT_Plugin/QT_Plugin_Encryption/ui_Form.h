/********************************************************************************
** Form generated from reading UI file 'Form.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_H
#define UI_FORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QComboBox *comboBox;
    QPlainTextEdit *plainTextEdit;
    QPushButton *encrypt_pushButton;
    QPushButton *decrypt_pushButton;
    QPushButton *decryptfile_pushButton;
    QPushButton *encryptfile_pushButton;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(400, 300);
        comboBox = new QComboBox(Form);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(40, 40, 69, 20));
        plainTextEdit = new QPlainTextEdit(Form);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(30, 90, 191, 141));
        encrypt_pushButton = new QPushButton(Form);
        encrypt_pushButton->setObjectName(QString::fromUtf8("encrypt_pushButton"));
        encrypt_pushButton->setGeometry(QRect(30, 250, 75, 23));
        decrypt_pushButton = new QPushButton(Form);
        decrypt_pushButton->setObjectName(QString::fromUtf8("decrypt_pushButton"));
        decrypt_pushButton->setGeometry(QRect(130, 250, 75, 23));
        decryptfile_pushButton = new QPushButton(Form);
        decryptfile_pushButton->setObjectName(QString::fromUtf8("decryptfile_pushButton"));
        decryptfile_pushButton->setGeometry(QRect(250, 180, 75, 23));
        encryptfile_pushButton = new QPushButton(Form);
        encryptfile_pushButton->setObjectName(QString::fromUtf8("encryptfile_pushButton"));
        encryptfile_pushButton->setGeometry(QRect(250, 230, 75, 23));

        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", nullptr));
        encrypt_pushButton->setText(QApplication::translate("Form", "\345\212\240\345\257\206\345\255\227\347\254\246\344\270\262", nullptr));
        decrypt_pushButton->setText(QApplication::translate("Form", "\350\247\243\345\257\206\345\255\227\347\254\246\344\270\262", nullptr));
        decryptfile_pushButton->setText(QApplication::translate("Form", "\350\247\243\345\257\206\346\226\207\346\234\254", nullptr));
        encryptfile_pushButton->setText(QApplication::translate("Form", "\345\212\240\345\257\206\346\226\207\346\234\254", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_H
