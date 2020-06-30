#include "Form.h"
#include "ui_Form.h"
#include <QDir>
#include <QString>
#include <QDebug>
#include <QFileDialog>
#include <functional>
#include <fstream>
#include "AES/aes.hpp"

//用于填充的数据
uint8_t fillArray[16] = { ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};

//用于检测是否已经被加密过
uint8_t encryptFlag[] = { "has been encrypt" };

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
    QString file = QFileDialog::getOpenFileName(this,
                        "选择文件",
                        "",
                        "all files (*.*)");
    qDebug() << file;
    encryptFile(file,file+".encry");
}

void Form::clickDecryptFileButton(bool click)
{
    QString file = QFileDialog::getOpenFileName(this,
                        "选择文件",
                        "",
                        "all files (*.*)");
    qDebug() << file;
    decryptFile(file,file+".decry");
}

int Form::encryptString(QString& str)
{
    return 0;
}

int Form::decryptString(QString& str)
{
    return 0;
}

int Form::encryptFile(const QString& infile,const QString& outfile)
{
    std::ifstream fs;
    fs.open(infile.toStdString().c_str(),std::ios::binary);
    if(fs.is_open())
    {
        /***********获取原始文件大小**************/
        fs.seekg(0,std::ios::end);
        uint64_t fileLen = fs.tellg();
        fs.seekg(0,std::ios::beg);
        m_pInterFaceStruct->pShowLogFunc("加密：文件大小：" + QString::number(fileLen));

        /***********计算填充字节**************/
        uint64_t fillByteSize = (16 - fileLen % 16)%16;//填充字节
        qDebug() << "加密：填充字节：" << fillByteSize;
        qDebug() << "加密：总长度：" << fillByteSize + fileLen;

        /***********读取文件数据**************/
        uint8_t *in = new uint8_t[fillByteSize + fileLen + sizeof(encryptFlag)];
        if(!in)
        {
            m_pInterFaceStruct->pShowLogFunc("无法申请到内存");
            fs.close();//关闭文件
            return -1;
        }
        fs.read((char*)(in + sizeof(encryptFlag)),fileLen);//读取文件数据，预留加密标记空间
        fs.close();//关闭文件

        /***********检测是否被加密过**************/
        if(0 == memcmp(in,encryptFlag,sizeof(encryptFlag)))
        {
            m_pInterFaceStruct->pShowLogFunc("加密：文件被加密过，无法再加密");
            delete[] in;
            return -1;
        }

        /***********进行填充**************/
        memcpy(in+ fileLen + sizeof(encryptFlag),fillArray,sizeof(uint8_t)*fillByteSize);//填充

        /***********进行加密**************/
        encrypt(in + sizeof(encryptFlag),fileLen+fillByteSize);

        /***********加上加密标记**************/
        uint64_t totalLen = fileLen + fillByteSize + sizeof(encryptFlag);
        qDebug() << "加密：标记字节：" << sizeof(encryptFlag);
        memcpy(in,encryptFlag,sizeof(encryptFlag));//加上加密标记

        /***********写入文件**************/
        std::ofstream outfs;
        outfs.open(outfile.toStdString().c_str(),std::ios::binary);
        if(outfs.is_open())
        {
            outfs.write((const char*)in,totalLen);
            outfs.close();
            delete[] in;
        }
        else
        {
            m_pInterFaceStruct->pShowLogFunc("加密：未打开文件");
            delete[] in;
            return -1;
        }
    }
    else
    {
        m_pInterFaceStruct->pShowLogFunc("加密：未打开文件");
        return -1;
    }

    return 0;
}

int Form::decryptFile(const QString& infile,const QString& outfile)
{
    std::ifstream fs;
    fs.open(infile.toStdString().c_str(),std::ios::binary);
    if(fs.is_open())
    {
        /***********读取文件**************/
        fs.seekg(0,std::ios::end);
        uint64_t len = fs.tellg();
        fs.seekg(0,std::ios::beg);
        m_pInterFaceStruct->pShowLogFunc("解密：文件大小：" + QString::number(len));
        uint8_t *in = new uint8_t[len];
        if(!in)
        {
            m_pInterFaceStruct->pShowLogFunc("解密：无法申请到内存");
            fs.close();//关闭文件
            return -1;
        }
        fs.read((char*)in,len);
        fs.close();

        /***********检测是否被加密过**************/
        qDebug() << "解密：标记字节：" << sizeof(encryptFlag);
        if(0 != memcmp(in,encryptFlag,sizeof(encryptFlag)))
        {
            m_pInterFaceStruct->pShowLogFunc("解密：文件未被加密过，无法解密");
            delete [] in;
            return -1;
        }

        /***********解密**************/
        decrypt(in + sizeof(encryptFlag),len-sizeof(encryptFlag));

        /***********去除填充字节**************/
        int i = len-1;
        for(;i > len-16; i--)
        {
            if(in[i] != fillArray[0])
            {
                break;
            }
        }
        uint64_t fillByteSize = len -1 -i;//计算填充字节
        qDebug() << "解密：填充字节：" << fillByteSize;

        /***********写入文件**************/
        std::ofstream outfs;
        outfs.open(outfile.toStdString().c_str(),std::ios::binary);
        if(outfs.is_open())
        {
            outfs.write((const char*)(in+sizeof(encryptFlag)),len - fillByteSize - sizeof(encryptFlag));
            outfs.close();
            delete [] in;
        }
        else
        {
            m_pInterFaceStruct->pShowLogFunc("解密：未打开文件");
            delete [] in;
             return -1;
        }
    }
    else
    {
        m_pInterFaceStruct->pShowLogFunc("解密：未打开文件");
        return -1;
    }

    return 0;
}

