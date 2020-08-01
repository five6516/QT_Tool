#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <functional>
#include <memory> // shared_ptr
#include <QListWidget>
#include <QStackedWidget>
#include <QTreeWidgetItem>
#include <QTreeWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLibrary>
#include <vector>
#include <map>
#include "ManagePlugin.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool showLogPlus(QString data, int R,int G,int B,int Size);
    bool showLog(QString data);
private:
    Ui::MainWindow *ui;

    QStackedWidget* m_pQStackedWidget;//放置插件窗口
    QTreeWidget* m_pQTreeWidget;//插件列表
    QListWidget* m_pQListWidget;//Log窗口
    std::map<std::string,CManagePlugin*> m_mapPlugin;//插件管理类

    InterFaceStruct* m_pInterFaceStruct;//接口
    int findPlugin();
    int initInterFace();

public slots:
    void treeItemPressed(QTreeWidgetItem *item,int column);
    void ItemDoubleClick(QListWidgetItem* item);
    void buttonVersion();
    void buttonSaveLog();
    void buttonClearLog();
    bool showLogPlusSlot(QString data, int R,int G,int B,int Size);
    bool showLogSlot(QString data);
};

#endif // MAINWINDOW_H
