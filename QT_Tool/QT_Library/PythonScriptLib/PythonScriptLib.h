#ifndef PYTHONSCRIPTLIB_H
#define PYTHONSCRIPTLIB_H

#include <QString>
#include <functional>
#include <QtCore/qglobal.h>
#if defined(PYTHONSCRIPTLIB_LIBRARY)
#  define PYTHONSCRIPTLIB_EXPORT Q_DECL_EXPORT
#else
#  define PYTHONSCRIPTLIB_EXPORT Q_DECL_IMPORT
#endif

typedef struct _Python_Param
{
    QString strAppPath;
    std::function<bool(QString, int,int,int,int)> pShowLog;
}Python_Param;

extern "C" PYTHONSCRIPTLIB_EXPORT int PythonScript_Run(Python_Param* Python_Param,QString moduleName,QString functionName,QString strInput1,QString strInput2,QString& strOutput);


#endif // PYTHONSCRIPTLIB_H
