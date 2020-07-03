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
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *label;
    QPlainTextEdit *plainTextEdit;
    QVBoxLayout *verticalLayout;
    QComboBox *comboBox;
    QPushButton *encryptfile_pushButton;
    QPushButton *decryptfile_pushButton;
    QPushButton *encrypt_pushButton;
    QPushButton *decrypt_pushButton;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(400, 300);
        gridLayout_2 = new QGridLayout(Form);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(Form);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        plainTextEdit = new QPlainTextEdit(Form);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));

        gridLayout->addWidget(plainTextEdit, 1, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        comboBox = new QComboBox(Form);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        verticalLayout->addWidget(comboBox);

        encryptfile_pushButton = new QPushButton(Form);
        encryptfile_pushButton->setObjectName(QString::fromUtf8("encryptfile_pushButton"));

        verticalLayout->addWidget(encryptfile_pushButton);

        decryptfile_pushButton = new QPushButton(Form);
        decryptfile_pushButton->setObjectName(QString::fromUtf8("decryptfile_pushButton"));

        verticalLayout->addWidget(decryptfile_pushButton);

        encrypt_pushButton = new QPushButton(Form);
        encrypt_pushButton->setObjectName(QString::fromUtf8("encrypt_pushButton"));

        verticalLayout->addWidget(encrypt_pushButton);

        decrypt_pushButton = new QPushButton(Form);
        decrypt_pushButton->setObjectName(QString::fromUtf8("decrypt_pushButton"));

        verticalLayout->addWidget(decrypt_pushButton);


        gridLayout_2->addLayout(verticalLayout, 0, 1, 1, 1);


        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", nullptr));
        label->setText(QApplication::translate("Form", "<html><head/><body><p><span style=\" color:#ff0000;\">\345\212\240\345\257\206\350\247\243\345\257\206\346\226\207\344\273\266\344\274\232\350\246\206\347\233\226\345\216\237\346\234\211\346\226\207\344\273\266\357\274\214\350\257\267\346\263\250\346\204\217\345\244\207\344\273\275\357\274\201</span></p><p><span style=\" color:#ff0000;\">\346\226\207\344\273\266/\346\226\207\344\273\266\345\244\271\345\212\240\350\247\243\345\257\206\347\233\264\346\216\245\346\213\226\345\205\245\345\215\263\345\217\257</span></p></body></html>", nullptr));
        encryptfile_pushButton->setText(QApplication::translate("Form", "\345\212\240\345\257\206\346\226\207\344\273\266", nullptr));
        decryptfile_pushButton->setText(QApplication::translate("Form", "\350\247\243\345\257\206\346\226\207\344\273\266", nullptr));
        encrypt_pushButton->setText(QApplication::translate("Form", "\345\212\240\345\257\206\345\255\227\347\254\246\344\270\262", nullptr));
        decrypt_pushButton->setText(QApplication::translate("Form", "\350\247\243\345\257\206\345\255\227\347\254\246\344\270\262", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_H
