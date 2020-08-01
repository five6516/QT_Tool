#ifndef CURRENTDOWNLOADINFOFORM_H
#define CURRENTDOWNLOADINFOFORM_H

#include <QWidget>
#include "QT_Plugin.h"
#include "curlPackage/curlSFTP.h"
#include "InformationDialog.h"

namespace Ui {
class CurrentDownloadInfoForm;
}

class CurrentDownloadInfoForm : public QWidget
{
    Q_OBJECT

public:
    explicit CurrentDownloadInfoForm(InterFaceStruct* pInterFaceStruct,QWidget *parent = nullptr);
    ~CurrentDownloadInfoForm();

    int startTask();

private:
    Ui::CurrentDownloadInfoForm *ui;
    InterFaceStruct* m_pInterFaceStruct;
    int m_nTimerID;
    bool m_bStartTask;

    int taskThread();
    int intervalHandle();

    curlSFTP* pSftp;
    InformationDialog* pInformationDlg;
protected:
    void timerEvent(QTimerEvent *event);
};

#endif // CURRENTDOWNLOADINFOFORM_H
