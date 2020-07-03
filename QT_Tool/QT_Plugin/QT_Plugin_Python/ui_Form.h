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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QGridLayout *gridLayout;
    QComboBox *comboBox;
    QSplitter *splitter;
    QPushButton *startButton;
    QPushButton *selectDirButton;
    QPushButton *selectFileButton;
    QPushButton *configButton;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(400, 300);
        gridLayout = new QGridLayout(Form);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        comboBox = new QComboBox(Form);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        gridLayout->addWidget(comboBox, 0, 0, 1, 1);

        splitter = new QSplitter(Form);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        startButton = new QPushButton(splitter);
        startButton->setObjectName(QString::fromUtf8("startButton"));
        splitter->addWidget(startButton);
        selectDirButton = new QPushButton(splitter);
        selectDirButton->setObjectName(QString::fromUtf8("selectDirButton"));
        splitter->addWidget(selectDirButton);
        selectFileButton = new QPushButton(splitter);
        selectFileButton->setObjectName(QString::fromUtf8("selectFileButton"));
        splitter->addWidget(selectFileButton);
        configButton = new QPushButton(splitter);
        configButton->setObjectName(QString::fromUtf8("configButton"));
        splitter->addWidget(configButton);

        gridLayout->addWidget(splitter, 1, 0, 1, 1);


        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", nullptr));
        startButton->setText(QApplication::translate("Form", "Start(&F)", nullptr));
        selectDirButton->setText(QApplication::translate("Form", "\351\200\211\346\213\251\346\226\207\344\273\266\345\244\271", nullptr));
        selectFileButton->setText(QApplication::translate("Form", "\351\200\211\346\213\251\346\226\207\344\273\266", nullptr));
        configButton->setText(QApplication::translate("Form", "\351\205\215\347\275\256\346\226\207\344\273\266", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_H
