#ifndef CURLSFTP_H
#define CURLSFTP_H
#include <QString>
#include <vector>
#include <mutex>
#include "curl/curl.h"

static bool bLibCurlGobalInit = false;

enum
{
    CURL_DIR,
    CURL_FILE,
};

typedef struct _REMOTE_FILE_INFO
{
    QString name;
    int type;//CURL_DIR:文件夹 CURL_FILE:文件
    QString permissions;
}REMOTE_FILE_INFO;

class curlSFTP
{
public:
    curlSFTP();
    ~curlSFTP();

    int dirlist(const QString& remote, std::vector<REMOTE_FILE_INFO> &vecFileInfo);//非递归
    int dirlistAll(const QString& remote, std::vector<REMOTE_FILE_INFO> &vecFileInfo);//递归文件夹

    int downloadFile(const QString& remotefilePath,const QString& localfilePath,u_int64 time_out);
    int downloadDir(const QString& remote,const QString& localPath,std::vector<REMOTE_FILE_INFO> &vecFileInfo,u_int64 time_out);

    int init();
    static void deleteGobalInit();

    //设置信息
    void setIP(const QString& IP);
    void setPort(int Port);
    void setUserName(const QString& UserName);
    void setPassword(const QString& Password);

    //获取信息
    size_t getSpeed();
    size_t getDownloadSize();
    size_t getTotalSize();
    size_t getDownloadTime();
    const char* getVersion();

private:
    QString m_strIP;
    int m_iPort;
    QString m_strUserName;
    QString m_strPassword;

    CURL *curl;
    CURLcode res;
    QString m_strError;
    std::mutex m_lock;
};

#endif // CURLSFTP_H

