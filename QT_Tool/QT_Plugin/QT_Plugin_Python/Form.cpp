#include "Form.h"
#include "ui_Form.h"
#include <QDir>
#include <QString>
#include <QFileDialog>
#include <functional>
#include <thread>
#include "../../QT_Library/PythonScriptLib/PythonScriptLib.h"
#pragma execution_character_set("utf-8")

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);

    QDir dir(QString().asprintf("%s/Plugin/Script",qApp->applicationDirPath().toStdString().c_str()));
    QStringList nameFilters;
    nameFilters << "*.py";
    ui->comboBox->clear(); //清除列表
    foreach (QString file, dir.entryList(nameFilters, QDir::Files)) {
        ui->comboBox->addItem(file.split(".").at(0)); //不带图标
    }

    m_strSelectDirName = qApp->applicationDirPath();
    m_strSelectFileName = qApp->applicationDirPath();
    m_strModuleName = ui->comboBox->currentText();
    m_strFunctionName = QString("Function");

    connect(ui->comboBox,SIGNAL(currentTextChanged(QString)),this,SLOT(ComBoxChange(QString)));
    connect(ui->listWidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(ItemDoubleClick(QListWidgetItem*)));
    connect(ui->startButton,SIGNAL(clicked(bool)),this,SLOT(ButtonStart(bool)));
    connect(ui->selectFileButton,SIGNAL(clicked(bool)),this,SLOT(ButtonSelectFile(bool)));
    connect(ui->selectDirButton,SIGNAL(clicked(bool)),this,SLOT(ButtonSelectDir(bool)));
    connect(ui->saveLogButton,SIGNAL(clicked(bool)),this,SLOT(ButtonSaveLog(bool)));
    connect(ui->clearLogButton,SIGNAL(clicked(bool)),this,SLOT(ButtonClearLog(bool)));
    connect(ui->configButton,SIGNAL(clicked(bool)),this,SLOT(ButtonConfig(bool)));
}

Form::~Form()
{
    delete ui;
}

void Form::ButtonStart(bool check)
{
    std::thread buttonThread(_thread_start,this);
    buttonThread.detach();
}

#include "Windows.h"
void Form::ButtonConfig(bool check)
{
    QString command = QString().asprintf("cmd /c notepad %s/Plugin/Script/config.ini",qApp->applicationDirPath().toStdString().c_str());
    //system(command.toStdString().c_str());
    WinExec(command.toStdString().c_str(),SW_HIDE);
}

void Form::ButtonSelectDir(bool check)
{
    m_strSelectDirName = QFileDialog::getExistingDirectory(
            this,
            tr("select a dir."),
            qApp->applicationDirPath());
}

void Form::ButtonSelectFile(bool check)
{
    m_strSelectFileName = QFileDialog::getOpenFileName(
            this,
            tr("select a file."),
            qApp->applicationDirPath(),
            tr("All files(*.*)"));
}



void Form::ButtonSaveLog(bool check)
{
   QString fileName = QFileDialog::getSaveFileName(
            this,
            tr("select a file."),
            QString().asprintf("%s\\log.txt",qApp->applicationDirPath().toStdString().c_str()),
            tr("log(*.txt);All files(*.*)"));

   QFile file(fileName);
   bool bOpen=file.open(QIODevice::ReadWrite|QIODevice::Truncate|QIODevice::Text);
   if (!bOpen)
   {
       ShowLog("save to file Error,openfile error");
       return;
   }

   for (int j = 0; j < ui->listWidget->count(); j++)
   {
       QString itemText = ui->listWidget->item(j)->text() + "\n";
       file.write(itemText.toStdString().c_str());
   }
   file.close();
}

void Form::ButtonClearLog(bool check)
{
    ui->listWidget->clear();
}

void Form::_thread_start(void* pVoid)
{
    Form* p =(Form*)pVoid;

    QString strOutput;
    Python_Param* pPython_Param = new Python_Param;
    pPython_Param->strAppPath = qApp->applicationDirPath() + "/Plugin/Script";
    pPython_Param->pShowLog = std::bind(&Form::ShowLog,p,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4,std::placeholders::_5);
    PythonScript_Run(pPython_Param,p->m_strModuleName,p->m_strFunctionName,p->m_strSelectDirName,p->m_strSelectFileName,strOutput);
    p->ShowLog("返回:"+strOutput,255,0,0,0);
}

bool Form::ShowLog(QString data, int R,int G,int B,int Size)
{
    QListWidgetItem *listItem = new QListWidgetItem(data);
    listItem->setSizeHint(QSize(60, 25));  // use to change the height
    listItem->setForeground(QBrush(QColor(R,G,B)));

    ui->listWidget->insertItem(ui->listWidget->count(), listItem);
    ui->listWidget->scrollToBottom();

    return true;
}

bool Form::ShowLogPy(QString data, int R,int G,int B,int Size)
{
    QListWidgetItem *listItem = new QListWidgetItem("Py:"+data);
    listItem->setSizeHint(QSize(60, 25));  // use to change the height
    listItem->setForeground(QBrush(QColor(R,G,B)));

    ui->listWidget->insertItem(ui->listWidget->count(), listItem);
    ui->listWidget->scrollToBottom();

    return true;
}

void Form::ComBoxChange(QString text)
{
    m_strModuleName = text;
}

void Form::ItemDoubleClick(QListWidgetItem* item)
{
    item->setFlags(item->flags() | Qt::ItemIsEditable);
}
