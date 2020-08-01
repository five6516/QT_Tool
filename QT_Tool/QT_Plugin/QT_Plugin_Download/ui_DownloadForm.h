/********************************************************************************
** Form generated from reading UI file 'DownloadForm.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOWNLOADFORM_H
#define UI_DOWNLOADFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CurrentDownloadInfoForm
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_name;
    QLabel *label_size;
    QHBoxLayout *horizontalLayout_2;
    QProgressBar *progressBar;
    QLabel *label_speed;
    QPushButton *pushButton;

    void setupUi(QWidget *CurrentDownloadInfoForm)
    {
        if (CurrentDownloadInfoForm->objectName().isEmpty())
            CurrentDownloadInfoForm->setObjectName(QString::fromUtf8("CurrentDownloadInfoForm"));
        CurrentDownloadInfoForm->resize(400, 300);
        verticalLayout = new QVBoxLayout(CurrentDownloadInfoForm);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_name = new QLabel(CurrentDownloadInfoForm);
        label_name->setObjectName(QString::fromUtf8("label_name"));

        horizontalLayout->addWidget(label_name);

        label_size = new QLabel(CurrentDownloadInfoForm);
        label_size->setObjectName(QString::fromUtf8("label_size"));

        horizontalLayout->addWidget(label_size);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        progressBar = new QProgressBar(CurrentDownloadInfoForm);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(0);

        horizontalLayout_2->addWidget(progressBar);

        label_speed = new QLabel(CurrentDownloadInfoForm);
        label_speed->setObjectName(QString::fromUtf8("label_speed"));

        horizontalLayout_2->addWidget(label_speed);

        pushButton = new QPushButton(CurrentDownloadInfoForm);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout_2->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(CurrentDownloadInfoForm);

        QMetaObject::connectSlotsByName(CurrentDownloadInfoForm);
    } // setupUi

    void retranslateUi(QWidget *CurrentDownloadInfoForm)
    {
        CurrentDownloadInfoForm->setWindowTitle(QApplication::translate("CurrentDownloadInfoForm", "Form", nullptr));
        label_name->setText(QApplication::translate("CurrentDownloadInfoForm", "*", nullptr));
        label_size->setText(QApplication::translate("CurrentDownloadInfoForm", "*", nullptr));
        label_speed->setText(QApplication::translate("CurrentDownloadInfoForm", "*", nullptr));
        pushButton->setText(QApplication::translate("CurrentDownloadInfoForm", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CurrentDownloadInfoForm: public Ui_CurrentDownloadInfoForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOWNLOADFORM_H
