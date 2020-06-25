#ifndef CMANAGEPLUGIN_H
#define CMANAGEPLUGIN_H
#include <QString>
#include <QLibrary>

class CManagePlugin
{
public:
    CManagePlugin();

    bool isPlugin(const QString& fileName);
    void releasePlugin();
    QWidget* pluginWidget();
    const char* pluginName();
    const char* pluginContent();

    void setIndex(int index);
    int getIndex();
private:
    int m_index;
    QLibrary m_Lib;
    typedef QWidget*(*QT_Plugin_Init)();
    typedef const char*(*QT_Plugin_Name)();
    typedef const char*(*QT_Plugin_Contents)();

    QT_Plugin_Init pQT_Plugin_Init;
    QT_Plugin_Name pQT_Plugin_Name;
    QT_Plugin_Contents pQT_Plugin_Contents;
};

#endif // CMANAGEPLUGIN_H
