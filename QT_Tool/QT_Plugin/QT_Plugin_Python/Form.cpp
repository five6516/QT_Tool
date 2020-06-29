#include "Form.h"
#include "ui_Form.h"
#include <QDir>
#include <QString>
#include <QFileDialog>
#include <functional>
#include <thread>
#include "../../QT_Library/PythonScriptLib/PythonScriptLib.h"
#pragma execution_character_set("utf-8")

Form::Form(InterFaceStruct* pInterFaceStruct,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form),
    m_pInterFaceStruct(pInterFaceStruct)
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
    connect(ui->startButton,SIGNAL(clicked(bool)),this,SLOT(ButtonStart(bool)));
    connect(ui->selectFileButton,SIGNAL(clicked(bool)),this,SLOT(ButtonSelectFile(bool)));
    connect(ui->selectDirButton,SIGNAL(clicked(bool)),this,SLOT(ButtonSelectDir(bool)));
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


void Form::_thread_start(void* pVoid)
{
    Form* p =(Form*)pVoid;

    QString strOutput;
    Python_Param* pPython_Param = new Python_Param;
    pPython_Param->strAppPath = qApp->applicationDirPath() + "/Plugin/Script";
    pPython_Param->pShowLog = p->m_pInterFaceStruct->pShowLogPlusFunc;
    PythonScript_Run(pPython_Param,p->m_strModuleName,p->m_strFunctionName,p->m_strSelectDirName,p->m_strSelectFileName,strOutput);
    p->m_pInterFaceStruct->pShowLogPlusFunc("返回:"+strOutput,255,0,0,0);
}

bool Form::ShowLogPy(QString data, int R,int G,int B,int Size)
{
    return m_pInterFaceStruct->pShowLogPlusFunc("Py:"+data,R,G,B,Size);
}

void Form::ComBoxChange(QString text)
{
    m_strModuleName = text;
}
