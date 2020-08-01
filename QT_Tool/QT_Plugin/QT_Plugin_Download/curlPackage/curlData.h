#ifndef CLIBCURLDATA_H
#define CLIBCURLDATA_H

#include <QString>
#include <QFile>
#include <QDebug>
#include "curl/curl.h"

namespace libcurlData {

static size_t writeStringCallBack(void *buffer, size_t size, size_t nmemb, void *userp)
{
    QString* pStrData = (QString*)userp;
    char* tempbuffer = new char[size*nmemb+1];
    memcpy(tempbuffer,buffer,size*nmemb);
    tempbuffer[size*nmemb] = '\0';//结束符
    pStrData->append(tempbuffer);
    delete [] tempbuffer;

    return size*nmemb;
}

static size_t writeFileCallBack(void *buffer, size_t size, size_t nmemb, void *userp)
{
    QFile * pfp = (QFile*)userp;
    if(pfp)
    {
        return pfp->write((const char*)buffer,size*nmemb);
    }
    return size*nmemb;
}

}

#endif // CLIBCURLDATA_H
