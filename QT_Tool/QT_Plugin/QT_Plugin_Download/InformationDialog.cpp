#include "InformationDialog.h"
#include "ui_InformationDialog.h"

#pragma execution_character_set("utf-8")
InformationDialog::InformationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InformationDialog)
{
    ui->setupUi(this);

}

InformationDialog::~InformationDialog()
{
    delete ui;
}

void InformationDialog::getDownloadInfo()
{
    downloadInfoStruct.ip = ui->lineEdit_ip->text();
    downloadInfoStruct.username = ui->lineEdit_username->text();
    downloadInfoStruct.password = ui->lineEdit_password->text();
    downloadInfoStruct.remotepath = ui->plainTextEdit_remotepath->toPlainText();
    downloadInfoStruct.localpath = ui->plainTextEdit_localpath->toPlainText();
}
