#pragma execution_character_set("utf-8")
#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <thread>
#include <string>
#include <QDir>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("QT Tool");
    m_pQStackedWidget = new QStackedWidget();
    ui->treeWidget->clear();

    //寻找插件
    QDir fileDir(qApp->applicationDirPath() + "/Plugin");
    fileDir.setFilter(QDir::Files);
    QFileInfoList fileInfoList = fileDir.entryInfoList();
    QStringList fileList;
    qDebug()<<fileInfoList .count();
    int i=0;
    for(int inf = 0; inf < fileInfoList .count(); inf ++)
    {
        QString fileName = fileInfoList.at(inf).absoluteFilePath();
        qDebug()<<fileName;
        CManagePlugin* pManagePlugin = new CManagePlugin;
        if(pManagePlugin->isPlugin(fileName))
        {
            qDebug()<<fileName<< "is Plugin";
            //不存在相同名字的插件，如果有，则不加载
            if(m_mapPlugin.find(std::string(pManagePlugin->pluginName())) == m_mapPlugin.end())
            {
                pManagePlugin->setIndex(i++);
                m_mapPlugin.insert(std::pair<std::string,CManagePlugin*>(std::string(pManagePlugin->pluginName()),pManagePlugin));
            }
            else
            {
                qDebug()<<fileName<< "has same name Plugin";
            }
        }
    }
    //加入控件界面
    for(auto plugin : m_mapPlugin)
    {
        QWidget* pWidget = plugin.second->pluginWidget();
        m_pQStackedWidget->addWidget(pWidget);//加入QStackedWidget
        qDebug()<< "add" << plugin.second->pluginName();

        QList<QTreeWidgetItem*> listTree = ui->treeWidget->findItems(QString(plugin.second->pluginContent()),Qt::MatchExactly);
        if(listTree.size() == 0)//是否存在相同根节点名
        {
            QTreeWidgetItem *group=new QTreeWidgetItem(ui->treeWidget);
            group->setText(0,plugin.second->pluginContent());
            QTreeWidgetItem *item=new QTreeWidgetItem(group);
            item->setText(0,plugin.second->pluginName());
            ui->treeWidget->addTopLevelItem(group);
        }
        else
        {
            for(auto root : listTree)
            {
                qDebug()<< root->text(0);
                if(root->text(0) == QString(plugin.second->pluginContent()))//添加到现有根节点
                {
                    QTreeWidgetItem *item=new QTreeWidgetItem(root);
                    item->setText(0,plugin.second->pluginName());
                    break;
                }
            }
        }


    }

    ui->treeWidget->expandAll();//展开

    ui->horizontalLayout->addWidget(m_pQStackedWidget);
    ui->horizontalLayout->setStretch(0,1);
    ui->horizontalLayout->setStretch(1,6);

    connect(ui->ac_version,SIGNAL(triggered()),this,SLOT(ButtonVersion()));
    connect(ui->treeWidget,SIGNAL(itemPressed(QTreeWidgetItem *,int)),this,SLOT(treeItemPressed(QTreeWidgetItem*,int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::ButtonVersion()
{
    QMessageBox::information(NULL, "Version", "hjfang\n1.0.0.0");
}


void MainWindow::treeItemPressed(QTreeWidgetItem *item, int column)
{
    //切换页面
    if(m_mapPlugin.find(item->text(column).toStdString()) != m_mapPlugin.end())
    {
        qDebug() << m_mapPlugin.find(item->text(column).toStdString())->second->getIndex();
        m_pQStackedWidget->setCurrentIndex(m_mapPlugin.find(item->text(column).toStdString())->second->getIndex());
    }
}

