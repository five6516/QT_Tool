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
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QGridLayout *gridLayout;
    QSplitter *splitter;
    QPushButton *startButton;
    QPushButton *selectFileButton;
    QPushButton *selectDirButton;
    QPushButton *configButton;
    QPushButton *saveLogButton;
    QPushButton *clearLogButton;
    QVBoxLayout *verticalLayout;
    QComboBox *comboBox;
    QListWidget *listWidget;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(400, 300);
        gridLayout = new QGridLayout(Form);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        splitter = new QSplitter(Form);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Vertical);
        startButton = new QPushButton(splitter);
        startButton->setObjectName(QString::fromUtf8("startButton"));
        splitter->addWidget(startButton);
        selectFileButton = new QPushButton(splitter);
        selectFileButton->setObjectName(QString::fromUtf8("selectFileButton"));
        splitter->addWidget(selectFileButton);
        selectDirButton = new QPushButton(splitter);
        selectDirButton->setObjectName(QString::fromUtf8("selectDirButton"));
        splitter->addWidget(selectDirButton);
        configButton = new QPushButton(splitter);
        configButton->setObjectName(QString::fromUtf8("configButton"));
        splitter->addWidget(configButton);
        saveLogButton = new QPushButton(splitter);
        saveLogButton->setObjectName(QString::fromUtf8("saveLogButton"));
        splitter->addWidget(saveLogButton);
        clearLogButton = new QPushButton(splitter);
        clearLogButton->setObjectName(QString::fromUtf8("clearLogButton"));
        splitter->addWidget(clearLogButton);

        gridLayout->addWidget(splitter, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        comboBox = new QComboBox(Form);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        verticalLayout->addWidget(comboBox);

        listWidget = new QListWidget(Form);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        verticalLayout->addWidget(listWidget);


        gridLayout->addLayout(verticalLayout, 0, 1, 1, 1);


        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", nullptr));
        startButton->setText(QApplication::translate("Form", "Start(&F)", nullptr));
        selectFileButton->setText(QApplication::translate("Form", "\351\200\211\346\213\251\346\226\207\344\273\266", nullptr));
        selectDirButton->setText(QApplication::translate("Form", "\351\200\211\346\213\251\346\226\207\344\273\266\345\244\271", nullptr));
        configButton->setText(QApplication::translate("Form", "\351\205\215\347\275\256\346\226\207\344\273\266", nullptr));
        saveLogButton->setText(QApplication::translate("Form", "\344\277\235\345\255\230log", nullptr));
        clearLogButton->setText(QApplication::translate("Form", "\346\270\205\347\251\272log", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_H
