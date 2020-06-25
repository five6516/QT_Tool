#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QListWidgetItem>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();

    static void _thread_start(void* pVoid);
    bool ShowLog(QString data, int R=0,int G=0,int B=0,int Size=0);
    bool ShowLogPy(QString data, int R=0,int G=0,int B=0,int Size=0);

    QString m_strModuleName;
    QString m_strFunctionName;
    QString m_strSelectDirName;
    QString m_strSelectFileName;
public slots:
    void ComBoxChange(QString text);
    void ItemDoubleClick(QListWidgetItem* item);

    void ButtonStart(bool check);
    void ButtonSelectDir(bool check);
    void ButtonSelectFile(bool check);
    void ButtonSaveLog(bool check);
    void ButtonClearLog(bool check);
    void ButtonConfig(bool check);

private:
    Ui::Form *ui;
};

#endif // FORM_H
