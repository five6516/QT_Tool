#ifndef QT_PLUGIN_H
#define QT_PLUGIN_H
#include <QtCore/qglobal.h>
#include <QWidget>

#if defined(QT_PLUGIN_LIBRARY)
#  define QT_PLUGIN_EXPORT Q_DECL_EXPORT
#else
#  define QT_PLUGIN_EXPORT Q_DECL_IMPORT
#endif


extern "C" QT_PLUGIN_EXPORT QWidget* QT_Plugin_Init();//界面
extern "C" QT_PLUGIN_EXPORT const char* QT_Plugin_Name();//插件名
extern "C" QT_PLUGIN_EXPORT const char* QT_Plugin_Contents();//插件目录

#endif // QT_PL_PYSCRIPT_H
