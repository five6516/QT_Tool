#include "Form.h"
#include "ui_Form.h"
#include <QDir>
#include <QString>
#include <QDebug>
#include <functional>
#include <fstream>
#include "AES/aes.hpp"

static QString phex(uint8_t len,uint8_t* str)
{
    QString strValue;
    unsigned char i;
    for (i = 0; i < len; ++i)
        strValue += QString::asprintf("%.2x",str[i]);
    return  strValue;
}

static void hexStringToCharArray(QString strValue,uint8_t* str)
{
    char arr[2];
    int j = 0;
    int k = 0;
    for(int i=0; i<strValue.length(); i++)
    {
        if (j == 0)
        {
            arr[j] = strValue.at(i).toLatin1();
            j = 1;
        }
        else
        {
            arr[j] = strValue.at(i).toLatin1();
            char *stop;
            str[k] = strtol(arr,&stop,16);
            k++;
            j = 0;
        }
    }
}

#pragma execution_character_set("utf-8")
Form::Form(InterFaceStruct* pInterFaceStruct,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form),
    m_pInterFaceStruct(pInterFaceStruct)
{
    ui->setupUi(this);

    connect(ui->encrypt_pushButton,SIGNAL(clicked(bool)),this,SLOT(clickEncryptButton(bool)));
    connect(ui->decrypt_pushButton,SIGNAL(clicked(bool)),this,SLOT(clickDecryptButton(bool)));
    connect(ui->encryptfile_pushButton,SIGNAL(clicked(bool)),this,SLOT(clickEncryptFileButton(bool)));
    connect(ui->decryptfile_pushButton,SIGNAL(clicked(bool)),this,SLOT(clickDecryptFileButton(bool)));


}

Form::~Form()
{
    delete ui;
}

int Form::encrypt(uint8_t* in,int len)
{
    uint8_t key[] = { 0x2b, 0x6e, 0x17, 0x16, 0x28, 0xae, 0xd3, 0xa6, 0xab, 0xf7, 0x15, 0x89, 0x09, 0xcf, 0x4f, 0x3c };
    uint8_t iv[]  = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };

    struct AES_ctx ctx;
    AES_init_ctx_iv(&ctx, key, iv);
    AES_CBC_encrypt_buffer(&ctx, in, len);

    return 0;
}

int Form::decrypt(uint8_t* in,int len)
{
    uint8_t key[] = { 0x2b, 0x6e, 0x17, 0x16, 0x28, 0xae, 0xd3, 0xa6, 0xab, 0xf7, 0x15, 0x89, 0x09, 0xcf, 0x4f, 0x3c };
    uint8_t iv[]  = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };

    struct AES_ctx ctx;
    AES_init_ctx_iv(&ctx, key, iv);
    AES_CBC_decrypt_buffer(&ctx, in, len);

    return 0;
}
#include <memory>
void Form::clickEncryptButton(bool click)
{
    QByteArray strValue = ui->plainTextEdit->toPlainText().toLocal8Bit();
    int size = strValue.size();
    m_pInterFaceStruct->pShowLogFunc("长度：" + QString::number(size));

    uint8_t in[2048];
    memcpy(in,strValue.data(),size);

    m_pInterFaceStruct->pShowLogFunc("原始字符串：" + QString((const char*)in));
    encrypt(in,size);
    m_pInterFaceStruct->pShowLogFunc("加密二进制：" + phex(size,in));
}

void Form::clickDecryptButton(bool click)
{
    QString strValue = ui->plainTextEdit->toPlainText();
    int size = strValue.toStdString().size();
    m_pInterFaceStruct->pShowLogFunc("长度：" + QString::number(size));

    uint8_t *in = new uint8_t[size/2];
    hexStringToCharArray(strValue,in);

    m_pInterFaceStruct->pShowLogFunc("原始二进制字符串：" + phex(size/2,in));
    decrypt(in,size/2);
    m_pInterFaceStruct->pShowLogFunc("解密字符串：" + QString((const char*)in));

    //delete [] in;
}

void Form::clickEncryptFileButton(bool click)
{
    uint8_t *in = nullptr;
    std::ifstream fs;
    fs.open("F:\\1.txt",std::ios::binary);
    if(fs)
    {

        fs.seekg(0,std::ios::end);
        long len = fs.tellg();
        m_pInterFaceStruct->pShowLogFunc("长度：" + QString::number(len));
        in = new uint8_t[len];
        fs.read((char*)in,len);
        fs.close();
        encrypt(in,len);
        std::ofstream outfs;
        outfs.open("F:\\2.txt",std::ios::binary);
        outfs.write((const char*)in,len);
        outfs.close();
    }
    else
    {
        m_pInterFaceStruct->pShowLogFunc("未打开文本");
    }

}

void Form::clickDecryptFileButton(bool click)
{
    uint8_t *in = nullptr;
    std::ifstream fs;
    fs.open("F:\\2.txt",std::ios::binary);
    if(fs)
    {
        fs.seekg(0,std::ios::end);
        long len = fs.tellg();
        m_pInterFaceStruct->pShowLogFunc("长度：" + QString::number(len));
        in = new uint8_t[len];
        fs.read((char*)in,len);
        fs.close();
        decrypt(in,len);
        std::ofstream outfs;
        outfs.open("F:\\3.txt",std::ios::binary);
        outfs.write((const char*)in,len);
        outfs.close();
    }
    else
    {
        m_pInterFaceStruct->pShowLogFunc("未打开文本");
    }
}

