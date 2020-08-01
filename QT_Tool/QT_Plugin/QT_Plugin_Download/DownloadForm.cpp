#include "DownloadForm.h"
#include "ui_DownloadForm.h"
#include <QDebug>
#include <future>
#include <thread>
#include <string>


#define TIMER_INTERVAL  (10)//定时器循环时间
#pragma execution_character_set("utf-8")
CurrentDownloadInfoForm::CurrentDownloadInfoForm(InterFaceStruct* pInterFaceStruct,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CurrentDownloadInfoForm),
    m_pInterFaceStruct(pInterFaceStruct)
{
    ui->setupUi(this);

    m_bStartTask = false;
    m_nTimerID = this->startTimer(TIMER_INTERVAL);
    pSftp = new curlSFTP();
    pInformationDlg = new InformationDialog();
}

CurrentDownloadInfoForm::~CurrentDownloadInfoForm()
{
    delete pSftp;
    delete ui;
}

void CurrentDownloadInfoForm::timerEvent(QTimerEvent *event)
{
    if(event->timerId() == m_nTimerID && m_bStartTask){
        intervalHandle();
    }
}

int CurrentDownloadInfoForm::intervalHandle()
{
    auto sizeFunc = [](size_t Size)->QString{
        if(Size<=1024)
        {
            return QString::asprintf("%d B",Size);
        }
        else if(Size<=1024*1024)
        {
            return QString::asprintf("%.2f KB",Size*1.0f/1024);
        }
        else
        {
            return QString::asprintf("%.2f MB",Size*1.0f/(1024*1024));
        }
    };

    if(pSftp)
    {
        ui->label_name->setText(pInformationDlg->downloadInfoStruct.remotepath);

        //下载数据进度
        float percentStr = 0;
        if(pSftp->getTotalSize() != 0)
            percentStr = (pSftp->getDownloadSize()*1.0/pSftp->getTotalSize())*100;

        ui->label_size->setText(QString::asprintf("%s/%s",
                                                  sizeFunc(pSftp->getDownloadSize()).toStdString().c_str(),
                                                  sizeFunc(pSftp->getTotalSize()).toStdString().c_str()));
        ui->progressBar->setRange(0,pSftp->getTotalSize()); //设置进度条最小值和最大值(取值范围)
        ui->progressBar->setValue(pSftp->getDownloadSize());  //设置当前的运行值

        ui->label_speed->setText(QString::asprintf("%s/s",sizeFunc(pSftp->getSpeed()).toStdString().c_str()));

    }

    return 0;
}

int CurrentDownloadInfoForm::taskThread()
{
    qDebug() << "taskThread";

    pSftp->init();
    pSftp->setIP(pInformationDlg->downloadInfoStruct.ip);
    pSftp->setPort(22);
    pSftp->setUserName(pInformationDlg->downloadInfoStruct.username);
    pSftp->setPassword(pInformationDlg->downloadInfoStruct.password);

    m_bStartTask = true;
    int lastIndexdot = pInformationDlg->downloadInfoStruct.remotepath.lastIndexOf('.');
    int lastIndexgang = pInformationDlg->downloadInfoStruct.remotepath.lastIndexOf('/');
    if(lastIndexdot < 0 || lastIndexgang > lastIndexdot)//文件夹
    {
        std::vector<REMOTE_FILE_INFO> vecFileInfo;
        if(0 == pSftp->downloadDir(pInformationDlg->downloadInfoStruct.remotepath,pInformationDlg->downloadInfoStruct.localpath,vecFileInfo,200))
        {
            for(int i=0;i<vecFileInfo.size();i++) {
                //m_pInterFaceStruct->pShowLogFunc(QString::asprintf("%s,%d,%s",vecFileInfo[i].name.toStdString().c_str(),vecFileInfo[i].type,vecFileInfo[i].permissions.toStdString().c_str()));
            }
            m_pInterFaceStruct->pShowLogFunc("下载完成");
        }
        else
        {
            m_pInterFaceStruct->pShowLogFunc("下载失败");
        }
    }
    else
    {
        if(0 == pSftp->downloadFile(pInformationDlg->downloadInfoStruct.remotepath,pInformationDlg->downloadInfoStruct.localpath,200))
        {
            m_pInterFaceStruct->pShowLogFunc("下载完成");
        }
    }
    this->killTimer(m_nTimerID);
#ifdef SKIP_PEER_VERIFICATION
    /*
     * If you want to connect to a site who isn't using a certificate that is
     * signed by one of the certs in the CA bundle you have, you can skip the
     * verification of the server's certificate. This makes the connection
     * A LOT LESS SECURE.
     *
     * If you have a CA cert for the server stored someplace else than in the
     * default bundle, then the CURLOPT_CAPATH option might come handy for
     * you.
     */
    //curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
#endif

#ifdef SKIP_HOSTNAME_VERIFICATION
    /*
     * If the site you're connecting to uses a different host name that what
     * they have mentioned in their server certificate's commonName (or
     * subjectAltName) fields, libcurl will refuse to connect. You can skip
     * this check, but this will make the connection less secure.
     */
    //curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
#endif

    /* Perform the request, res will get the return code */

    return 0;
}

int CurrentDownloadInfoForm::startTask()
{
    pInformationDlg->setModal(false);
    if(QDialog::Accepted == pInformationDlg->exec())
    {
        pInformationDlg->getDownloadInfo();

        std::function<void()> f = std::bind(&CurrentDownloadInfoForm::taskThread,this);
        std::thread t(f);
        t.detach();
    }
    else
    {
        return -1;
    }

    return 0;
}
