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
    void addNewTaskInfoSlots();
    void buttonClick(bool check);

private:
    Ui::Form *ui;
    InterFaceStruct* m_pInterFaceStruct;
};

#endif // FORM_H
