#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QListWidgetItem>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
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
    void clickFormatButton(bool check);
    void clickCompressButton(bool check);

protected:
    void dropEvent(QDropEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
private:
    Ui::Form *ui;
    InterFaceStruct* m_pInterFaceStruct;
};

#endif // FORM_H
