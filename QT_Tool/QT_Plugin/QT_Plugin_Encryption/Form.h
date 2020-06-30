#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QListWidgetItem>
#include "QT_Plugin.h"

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(InterFaceStruct* pInterFaceStruct,QWidget *parent = nullptr);
    ~Form();

public slots:
    void clickEncryptButton(bool click);
    void clickDecryptButton(bool click);

    void clickEncryptFileButton(bool click);
    void clickDecryptFileButton(bool click);
private:
    Ui::Form *ui;
    InterFaceStruct* m_pInterFaceStruct;

    int encrypt(uint8_t* in,int len);
    int decrypt(uint8_t* in,int len);

    int encryptString(QString& str);
    int decryptString(QString& str);
    int encryptFile(const QString& infile,const QString& outfile);
    int decryptFile(const QString& infile,const QString& outfile);

};

#endif // FORM_H
