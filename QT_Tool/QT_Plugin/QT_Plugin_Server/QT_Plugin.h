#ifndef QT_PLUGIN_H
#define QT_PLUGIN_H
#include <QtCore/qglobal.h>
#include <QWidget>
#include <functional>

#if defined(QT_PLUGIN_LIBRARY)
#  define QT_PLUGIN_EXPORT Q_DECL_EXPORT
#else
#  define QT_PLUGIN_EXPORT Q_DECL_IMPORT
#endif

typedef struct _InterFaceStruct{
    std::function<bool(QString data)> pShowLogFunc;
    std::function<bool(QString data, int R,int G,int B,int Size)> pShowLogPlusFunc;
}InterFaceStruct;

extern "C" QT_PLUGIN_EXPORT QWidget* QT_Plugin_Init(InterFaceStruct* pInterFaceStruct);//初始化界面，传递接口
extern "C" QT_PLUGIN_EXPORT const char* QT_Plugin_Name();//插件名
extern "C" QT_PLUGIN_EXPORT const char* QT_Plugin_Contents();//插件目录

#endif // QT_PL_PYSCRIPT_H
