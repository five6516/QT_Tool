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

public slots:


private:
    Ui::Form *ui;
};

#endif // FORM_H
