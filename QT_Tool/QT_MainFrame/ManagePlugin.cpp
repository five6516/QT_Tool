#include "ManagePlugin.h"

CManagePlugin::CManagePlugin()
{
    pQT_Plugin_Init = nullptr;
    pQT_Plugin_Name = nullptr;
    pQT_Plugin_Contents = nullptr;
}

void CManagePlugin::setIndex(int index)
{
    m_index = index;
}

int CManagePlugin::getIndex()
{
    return m_index;
}

bool CManagePlugin::isPlugin(const QString& fileName)
{
    if(QLibrary::isLibrary(fileName))
    {
        //确认是否是动态库
        m_Lib.setFileName(fileName);
        if(m_Lib.load())//加载库成功
        {
            pQT_Plugin_Init = (QT_Plugin_Init)m_Lib.resolve("QT_Plugin_Init");
            pQT_Plugin_Name = (QT_Plugin_Name)m_Lib.resolve("QT_Plugin_Name");
            pQT_Plugin_Contents = (QT_Plugin_Contents)m_Lib.resolve("QT_Plugin_Contents");
            if(pQT_Plugin_Init != nullptr && pQT_Plugin_Name != nullptr &&
               pQT_Plugin_Contents != nullptr )
            {
                return true;
            }
        }
    }

    return false;
}

QWidget* CManagePlugin::pluginWidget(InterFaceStruct* pInterFaceStruct)
{
    if(pQT_Plugin_Init)
    {
        return pQT_Plugin_Init(pInterFaceStruct);
    }
    return nullptr;
}

const char* CManagePlugin::pluginName()
{
    if(pQT_Plugin_Name)
    {
        return pQT_Plugin_Name();
    }
    return "null";
}

const char* CManagePlugin::pluginContent()
{
    if(pQT_Plugin_Contents)
    {
        return pQT_Plugin_Contents();
    }
    return "null";
}


void CManagePlugin::releasePlugin()
{
    m_Lib.unload();
}
