#include "curlSFTP.h"
#include "curlData.h"
#include <QDebug>
#include <QFile>
#include <QDir>

curlSFTP::curlSFTP()
{

}

curlSFTP::~curlSFTP()
{
    if(curl)
    {
        curl_easy_cleanup(curl);
    }
}

int curlSFTP::init()
{
    m_lock.lock();
    if(!bLibCurlGobalInit)
    {
        curl_global_init(CURL_GLOBAL_DEFAULT);//全局的初始化功能，在整个程序中只能调用一次
        bLibCurlGobalInit = true;
    }
    m_lock.unlock();

    curl = curl_easy_init();
    if(curl == nullptr)
    {
        m_strError = "curl_easy_init fail";
        qDebug() << m_strError;
        return -1;
    }
    return 0;
}

void curlSFTP::deleteGobalInit()
{
    curl_global_cleanup();
}

void curlSFTP::setIP(const QString& IP)
{
    m_strIP= IP;
}

void curlSFTP::setPort(int Port)
{
    m_iPort = Port;
}

void curlSFTP::setUserName(const QString& UserName)
{
    m_strUserName = UserName;
}

void curlSFTP::setPassword(const QString& Password)
{
    m_strPassword = Password;
}

size_t curlSFTP::getSpeed()
{
    curl_off_t speed = 0;
    if(curl != nullptr)
        curl_easy_getinfo(curl, CURLINFO_SPEED_DOWNLOAD_T, &speed);

   return  speed;
}

size_t curlSFTP::getDownloadSize()
{
    curl_off_t dl = 0;
    if(curl != nullptr)
        curl_easy_getinfo(curl, CURLINFO_SIZE_DOWNLOAD_T, &dl);

   return  dl;
}

size_t curlSFTP::getTotalSize()
{
    curl_off_t cl = 0;
    if(curl != nullptr)
        curl_easy_getinfo(curl, CURLINFO_CONTENT_LENGTH_DOWNLOAD_T, &cl);

   return  cl;
}

size_t curlSFTP::getDownloadTime()
{
    curl_off_t curtime = 0;
    if(curl != nullptr)
        curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME_T, &curtime);

   return curtime;
}

const char* curlSFTP::getVersion()
{
    return curl_version();
}

int curlSFTP::downloadFile(const QString& remotefilePath,const QString& localfilePath,u_int64 time_out)
{
    qDebug() << "remotefilePath:" << remotefilePath;
    qDebug() << "localfilePath:" << localfilePath;

    if (curl == nullptr)
    {
        m_strError = "disconnect!";
        qDebug() << m_strError;
        return -1;
    }

    QString remotePath = remotefilePath;//CTools::replace(remote, "\\", "/" );

    QString url;
    url.append("sftp://");;
    url.append(m_strIP);
    url.append(":");
    url.append(QString::number(m_iPort));
    url.append("/");
    url.append(remotePath);
    qDebug() << "url:" << url;
    curl_easy_setopt(curl, CURLOPT_URL, url.toStdString().c_str());

    QString nameAndPw;
    nameAndPw.append(m_strUserName);
    nameAndPw.append(":");
    nameAndPw.append(m_strPassword);
    qDebug() << "pw:" << nameAndPw;

    curl_easy_setopt(curl, CURLOPT_USERPWD, nameAndPw.toStdString().c_str());

    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, libcurlData::writeFileCallBack);

    //创建文件夹
    int index = localfilePath.lastIndexOf('/');
    if(index>=0)
    {
        QString sPath = localfilePath.left(index);
        qDebug() << "dir:" << sPath;
        //文件不存在，先看路径是否存在
        QDir dir(sPath);
        if(!dir.exists(sPath))
        {
            dir.mkpath(sPath);
        }
    }

    //创建文件指针
    QFile file(localfilePath);
    if(!file.open(QIODevice::WriteOnly))
    {
        m_strError = "open localfile fail!";
        qDebug() << m_strError;
        return -1;
    }
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &file);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, time_out);
    res = curl_easy_perform(curl);
    if ( res != CURLE_OK )
    {
        m_strError = curl_easy_strerror( res );
        qDebug() << m_strError;
        return -1;
    }
    return 0;
}

int curlSFTP::downloadDir(const QString& remote,const QString& local,std::vector<REMOTE_FILE_INFO> &vecFileInfo,u_int64 time_out)
{
    //获取所有文件文件夹
    if(0!=dirlistAll(remote, vecFileInfo))
    {
        return -1;
    }

    //下载
    for(auto i:vecFileInfo)
    {
        if(i.type == CURL_FILE)//文件
        {
            QString localPath = "";
            localPath.append(local);
            localPath.append(i.name.mid(remote.size(),i.name.size()));
            downloadFile(i.name,localPath,time_out);
        }
    }
    return 0;
}

int curlSFTP::dirlist(const QString& remote, std::vector<REMOTE_FILE_INFO> &vecFileInfo)
{
    if (curl == nullptr)
    {
        m_strError = "sftp disconnect!";
        qDebug() << m_strError;
        return -1;
    }

    QString response;
    QString remotePath = remote;//CTools::replace(remote, "\\", "/" );
    if (remotePath.size() == 0 || remotePath[remotePath.length()-1] != '/')
    {
        remotePath.append("/");
    }

    QString url;
    url.append("sftp://");;
    url.append(m_strIP);
    url.append(":");
    url.append(QString::number(m_iPort));
    url.append("/");
    url.append(remotePath);
    qDebug() << "url:" << url;
    curl_easy_setopt(curl, CURLOPT_URL, url.toStdString().c_str());

    QString nameAndPw;
    nameAndPw.append(m_strUserName);
    nameAndPw.append(":");
    nameAndPw.append(m_strPassword);
    qDebug() << "pw:" << nameAndPw;

    curl_easy_setopt(curl, CURLOPT_USERPWD, nameAndPw.toStdString().c_str());
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, libcurlData::writeStringCallBack);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    res = curl_easy_perform(curl);
    if ( res != CURLE_OK )
    {
        m_strError = curl_easy_strerror( res );
        qDebug() << m_strError;
        return -1;
    }

    qDebug() << response;

    //解析ftp数据得到文件和文件夹属性
    size_t pos=0, index=0, len=0;
    while(true)
    {

        QString row= "";
        pos = response.indexOf("\n", pos) + 1;
        if (pos < index)
        {
            break;
        }
        len =  pos - index - 1;//需要截取的字符串长度, -1去除换行符
        row = response.mid(index, len); //得到每行数据
        index = pos;

        size_t rowPos=0, rowIndex=0, rowLen=0;
        //得到名称
        REMOTE_FILE_INFO fileInfo;
        //rowPos = row.find_last_of(' ')+1;

        int time_pos = row.indexOf(":");
        rowPos = row.indexOf(' ',time_pos)+1;

        QString name = row.mid(rowPos, row.length());
        if (name.size() == 0|| name == "." || name == "..")
        {
            continue;
        }

        fileInfo.name = name;
        //得到文件权限和文件类型
        rowPos = row.indexOf(' ');
        QString data = row.mid(0,rowPos);
        if ( data.size() != 0 )
        {
            if (data[0] == 'd')
            {
                //文件夹
                fileInfo.type = CURL_DIR;
                fileInfo.permissions = data.mid(1, data.length());
            }
            else
            {
                //文件
                fileInfo.type = CURL_FILE;
                fileInfo.permissions = data.mid(1, data.length());
            }
        }

        vecFileInfo.emplace_back(fileInfo);
    }

    return 0;
}

int curlSFTP::dirlistAll(const QString& remote, std::vector<REMOTE_FILE_INFO> &vecFileInfo)
{
    if (curl == nullptr)
    {
        m_strError = "sftp disconnect!";
        qDebug() << m_strError;
        return -1;
    }

    QString response;
    QString remotePath = remote;//CTools::replace(remote, "\\", "/" );
    if (remotePath.size() == 0 || remotePath[remotePath.length()-1] != '/')
    {
        remotePath.append("/");
    }

    QString url;
    url.append("sftp://");;
    url.append(m_strIP);
    url.append(":");
    url.append(QString::number(m_iPort));
    url.append("/");
    url.append(remotePath);
    qDebug() << "url:" << url;
    curl_easy_setopt(curl, CURLOPT_URL, url.toStdString().c_str());

    QString nameAndPw;
    nameAndPw.append(m_strUserName);
    nameAndPw.append(":");
    nameAndPw.append(m_strPassword);
    qDebug() << "pw:" << nameAndPw;

    curl_easy_setopt(curl, CURLOPT_USERPWD, nameAndPw.toStdString().c_str());

    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, libcurlData::writeStringCallBack);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    res = curl_easy_perform(curl);
    if ( res != CURLE_OK )
    {
        m_strError = curl_easy_strerror( res );
        qDebug() << m_strError;
        return -1;
    }

    qDebug() << response;

    //解析ftp数据得到文件和文件夹属性
    size_t pos=0, index=0, len=0;
    while(true)
    {
        QString row= "";
        pos = response.indexOf("\n", pos) + 1;
        if (pos < index)
        {
            break;
        }
        len =  pos - index - 1;//需要截取的字符串长度, -1去除换行符
        row = response.mid(index, len); //得到每行数据
        index = pos;

        std::string::size_type rowPos=0, rowIndex=0, rowLen=0;
        //得到名称
        REMOTE_FILE_INFO fileInfo;
        //rowPos = row.find_last_of(' ')+1;

        int time_pos = row.indexOf(":");
        rowPos = row.indexOf(' ',time_pos)+1;

        QString name = row.mid(rowPos, row.length());
        if (name.size() == 0|| name == "." || name == "..")
        {
            continue;
        }
        QString fullpath;
        fullpath.append(remote);
        fullpath.append("/");
        fullpath.append(name);
        fileInfo.name = fullpath;

        //得到文件权限和文件类型
        rowPos = row.indexOf(' ');
        QString data = row.mid(0,rowPos);
        if (data.size() != 0)
        {
            if (data[0] == 'd')
            {
                //文件夹
                fileInfo.type = CURL_DIR;
                fileInfo.permissions = data.mid(1, data.length());
                vecFileInfo.emplace_back(fileInfo);
                dirlistAll(fullpath, vecFileInfo);
            }
            else
            {
                //文件
                fileInfo.type = CURL_FILE;
                fileInfo.permissions = data.mid(1, data.length());
                vecFileInfo.emplace_back(fileInfo);
            }
        }
    }

    return 0;
}
