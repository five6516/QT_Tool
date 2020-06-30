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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QGridLayout *gridLayout;
    QPlainTextEdit *plainTextEdit;
    QVBoxLayout *verticalLayout;
    QComboBox *comboBox;
    QPushButton *decryptfile_pushButton;
    QPushButton *encryptfile_pushButton;
    QPushButton *encrypt_pushButton;
    QPushButton *decrypt_pushButton;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(400, 300);
        gridLayout = new QGridLayout(Form);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        plainTextEdit = new QPlainTextEdit(Form);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));

        gridLayout->addWidget(plainTextEdit, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        comboBox = new QComboBox(Form);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        verticalLayout->addWidget(comboBox);

        decryptfile_pushButton = new QPushButton(Form);
        decryptfile_pushButton->setObjectName(QString::fromUtf8("decryptfile_pushButton"));

        verticalLayout->addWidget(decryptfile_pushButton);

        encryptfile_pushButton = new QPushButton(Form);
        encryptfile_pushButton->setObjectName(QString::fromUtf8("encryptfile_pushButton"));

        verticalLayout->addWidget(encryptfile_pushButton);

        encrypt_pushButton = new QPushButton(Form);
        encrypt_pushButton->setObjectName(QString::fromUtf8("encrypt_pushButton"));

        verticalLayout->addWidget(encrypt_pushButton);

        decrypt_pushButton = new QPushButton(Form);
        decrypt_pushButton->setObjectName(QString::fromUtf8("decrypt_pushButton"));

        verticalLayout->addWidget(decrypt_pushButton);


        gridLayout->addLayout(verticalLayout, 0, 1, 1, 1);


        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", nullptr));
        decryptfile_pushButton->setText(QApplication::translate("Form", "\350\247\243\345\257\206\346\226\207\346\234\254", nullptr));
        encryptfile_pushButton->setText(QApplication::translate("Form", "\345\212\240\345\257\206\346\226\207\346\234\254", nullptr));
        encrypt_pushButton->setText(QApplication::translate("Form", "\345\212\240\345\257\206\345\255\227\347\254\246\344\270\262", nullptr));
        decrypt_pushButton->setText(QApplication::translate("Form", "\350\247\243\345\257\206\345\255\227\347\254\246\344\270\262", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_H
