#ifndef INFORMATIONDIALOG_H
#define INFORMATIONDIALOG_H

#include <QDialog>

typedef struct _DownloadInfoStruct
{
    QString ip;
    QString username;
    QString password;
    QString remotepath;
    QString localpath;
}DownloadInfoStruct;

namespace Ui {
class InformationDialog;
}

class InformationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InformationDialog(QWidget *parent = nullptr);
    ~InformationDialog();

    void getDownloadInfo();
    DownloadInfoStruct downloadInfoStruct;
private:
    Ui::InformationDialog *ui;
};

#endif // INFORMATIONDIALOG_H
