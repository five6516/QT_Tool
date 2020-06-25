#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <functional>
#include <memory> // shared_ptr
#include <QListWidget>
#include <QStackedWidget>
#include <QLibrary>
#include <vector>
#include <map>
#include "ManagePlugin.h"
#include "QTreeWidgetItem"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QStackedWidget* m_pQStackedWidget;//放置插件窗口
    std::map<std::string,CManagePlugin*> m_mapPlugin;//插件管理类

public slots:
    void treeItemPressed(QTreeWidgetItem *item,int column);
    void ButtonVersion();


};

#endif // MAINWINDOW_H
