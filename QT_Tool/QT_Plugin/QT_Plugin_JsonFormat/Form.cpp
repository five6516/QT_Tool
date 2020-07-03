#include "Form.h"
#include "ui_Form.h"
#include <QDir>
#include <QString>
#include <functional>
#include <QJsonDocument>

#pragma execution_character_set("utf-8")

const QString getErrorInfo(QJsonParseError error)
{
    switch (error.error) {
    case QJsonParseError::NoError:
        return "json格式OK";
    case QJsonParseError::UnterminatedObject:
        return "对象不正确地终止以右花括号结束";
    case QJsonParseError::MissingNameSeparator:
        return "分隔不同项的逗号丢失";
    case QJsonParseError::UnterminatedArray:
        return "数组不正确地终止以右中括号结束";
    case QJsonParseError::MissingValueSeparator:
        return "对象中分割 key/value 的冒号丢失";
    case QJsonParseError::IllegalValue:
        return "值是非法的";
    case QJsonParseError::TerminationByNumber:
        return "在解析数字时，输入流结束";
    case QJsonParseError::IllegalNumber:
        return "数字格式不正确";
    case QJsonParseError::IllegalEscapeSequence:
        return "在输入时，发生一个非法转义序列";
    case QJsonParseError::IllegalUTF8String:
        return "在输入时，发生一个非法 UTF8 序列";
    case QJsonParseError::UnterminatedString:
        return "字符串不是以引号结束";
    case QJsonParseError::MissingObject:
        return "一个对象是预期的，但是不能被发现";
    case QJsonParseError::DeepNesting:
        return "对解析器来说，JSON 文档嵌套太深";
    case QJsonParseError::DocumentTooLarge:
        return "对解析器来说，JSON 文档太大";
    case QJsonParseError::GarbageAtEnd:
        return "解析的文档在末尾处包含额外的乱码";
    default:
        break;
    }
    return "";
}


Form::Form(InterFaceStruct* pInterFaceStruct,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form),
    m_pInterFaceStruct(pInterFaceStruct)
{
    ui->setupUi(this);

    ui->textEdit->setText("{\"a\":{\"b\":1,\"c\":2}}");
    ui->textEdit->setAcceptDrops(false);
    this->setAcceptDrops(true);
    connect(ui->format_pushButton,SIGNAL(clicked(bool)),SLOT(clickFormatButton(bool)));
    connect(ui->compress_pushButton,SIGNAL(clicked(bool)),SLOT(clickCompressButton(bool)));
}

Form::~Form()
{
    delete ui;
}

void Form::clickFormatButton(bool check)
{
    QJsonParseError jsonError;
    QJsonDocument jdoc;
    jdoc = QJsonDocument::fromJson(ui->textEdit->toPlainText().toUtf8(),&jsonError);
    if(jsonError.error != QJsonParseError::NoError)
    {
        m_pInterFaceStruct->pShowLogFunc("异常:" + jsonError.errorString());
        m_pInterFaceStruct->pShowLogFunc(getErrorInfo(jsonError));
    }
    else
    {
        ui->textEdit->setText(jdoc.toJson(QJsonDocument::Indented));
    }
}

void Form::clickCompressButton(bool check)
{
    QJsonParseError jsonError;
    QJsonDocument jdoc;
    jdoc = QJsonDocument::fromJson(ui->textEdit->toPlainText().toUtf8(),&jsonError);
    if(jsonError.error != QJsonParseError::NoError)
    {
        m_pInterFaceStruct->pShowLogFunc("异常:" + jsonError.errorString());
        m_pInterFaceStruct->pShowLogFunc(getErrorInfo(jsonError));
    }
    else
    {
        ui->textEdit->setText(jdoc.toJson(QJsonDocument::Compact));
    }
}

void Form::dropEvent(QDropEvent *event)
{
    QList<QUrl> urls = event->mimeData()->urls();
    QString filePath = urls[0].toLocalFile();
    QFileInfo fileinfo(filePath);
    if(fileinfo.isFile())
    {
        QFile file(filePath);
        file.open(QIODevice::ReadOnly);
        if(file.isOpen())
        {
            ui->textEdit->setText(file.readAll());
            file.close();
        }
    }
}

void Form::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls())
        event->acceptProposedAction();
}
