#include "Form.h"
#include "ui_Form.h"
#include <QDir>
#include <QString>
#include <QListWidgetItem>
#include <QPushButton>
#include <QDebug>
#include <functional>
#include <future>
#include <thread>
#include "curlPackage/curlSFTP.h"
#include "DownloadForm.h"
#define SKIP_PEER_VERIFICATION
#define SKIP_HOSTNAME_VERIFICATION


#pragma execution_character_set("utf-8")
Form::Form(InterFaceStruct* pInterFaceStruct,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form),
    m_pInterFaceStruct(pInterFaceStruct)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked(bool)),SLOT(buttonClick(bool)));

}

Form::~Form()
{
    delete ui;
}

void Form::buttonClick(bool check)
{
    qDebug() << "按钮开始";
    QMetaObject::invokeMethod(this,"addNewTaskInfoSlots");
}

void Form::addNewTaskInfoSlots()
{
    QListWidgetItem *add_item = new QListWidgetItem(ui->listWidget);
    add_item->setSizeHint(QSize(200,50));
    CurrentDownloadInfoForm *pCurrentDownloadInfoForm = new CurrentDownloadInfoForm(m_pInterFaceStruct);
    if(0 == pCurrentDownloadInfoForm->startTask())
    {
        qDebug() << "startTask";
        ui->listWidget->setItemWidget(add_item,pCurrentDownloadInfoForm);
    }
    else
    {
        qDebug() << "deleteTask";
        delete add_item;
    }
}


