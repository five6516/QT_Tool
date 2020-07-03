#pragma execution_character_set("utf-8")
#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <thread>
#include <string>
#include <functional>
#include <QDir>
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("QT Tool");
    ui->statusBar->hide();//隐藏状态栏

    QAction *clearAct = new QAction("🆑");
    clearAct->setToolTip("清空log");
    //boldAct->setStatusTip(tr("Insert bold text or change selected text to bold"));
    connect(clearAct, SIGNAL(triggered()),this,SLOT(buttonClearLog()));
    QAction *saveAct = new QAction("💾");
    saveAct->setToolTip("保存log");
    connect(saveAct, SIGNAL(triggered()),this,SLOT(buttonSaveLog()));

    ui->mainToolBar->addAction(clearAct);
    ui->mainToolBar->addAction(saveAct);
    //ui->mainToolBar->hide();

    //初始化接口
    initInterFace();

    m_pQListWidget = new QListWidget();
    m_pQTreeWidget = new QTreeWidget();
    m_pQStackedWidget = new QStackedWidget();
    m_pQTreeWidget->clear();
    m_pQTreeWidget->setHeaderLabel("插件");

    //寻找插件
    findPlugin();

    //加入控件界面
    for(auto plugin : m_mapPlugin)
    {
        QWidget* pWidget = plugin.second->pluginWidget(m_pInterFaceStruct);
        m_pQStackedWidget->addWidget(pWidget);//加入QStackedWidget
        qDebug()<< "add" << plugin.second->pluginName();

        QList<QTreeWidgetItem*> listTree = m_pQTreeWidget->findItems(QString(plugin.second->pluginContent()),Qt::MatchExactly);
        if(listTree.size() == 0)//是否存在相同根节点名
        {
            QTreeWidgetItem *group=new QTreeWidgetItem(m_pQTreeWidget);
            group->setText(0,plugin.second->pluginContent());
            QTreeWidgetItem *item=new QTreeWidgetItem(group);
            item->setText(0,plugin.second->pluginName());
            m_pQTreeWidget->addTopLevelItem(group);
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

    m_pQTreeWidget->expandAll();//展开

    QVBoxLayout *pQVBoxLayout = new QVBoxLayout();
    pQVBoxLayout->addWidget(m_pQStackedWidget);
    pQVBoxLayout->addWidget(m_pQListWidget);
    pQVBoxLayout->setStretch(0,2);
    pQVBoxLayout->setStretch(1,1);

    QHBoxLayout *pQHBoxLayout = new QHBoxLayout();
    pQHBoxLayout->addWidget(m_pQTreeWidget);
    pQHBoxLayout->addLayout(pQVBoxLayout);
    pQHBoxLayout->setStretch(0,1);
    pQHBoxLayout->setStretch(1,6);

    QGridLayout *pQGridLayout = new QGridLayout(ui->centralWidget);
    pQGridLayout->addLayout(pQHBoxLayout,0,1);

    ui->centralWidget->setLayout(pQVBoxLayout);

    connect(ui->ac_version,SIGNAL(triggered()),this,SLOT(buttonVersion()));
    connect(m_pQTreeWidget,SIGNAL(itemPressed(QTreeWidgetItem *,int)),this,SLOT(treeItemPressed(QTreeWidgetItem*,int)));
    connect(m_pQListWidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(ItemDoubleClick(QListWidgetItem*)));
}

MainWindow::~MainWindow()
{
    delete m_pInterFaceStruct;
    delete ui;
}

int MainWindow::initInterFace()
{
    m_pInterFaceStruct = new InterFaceStruct();
    m_pInterFaceStruct->pShowLogFunc = std::bind(&MainWindow::showLog,this,std::placeholders::_1);
    m_pInterFaceStruct->pShowLogPlusFunc = std::bind(&MainWindow::showLogPlus,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4,std::placeholders::_5);

    return 0;
}

int MainWindow::findPlugin()
{
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

    return  0;
}

bool MainWindow::showLogPlus(QString data, int R,int G,int B,int Size)
{
    QListWidgetItem *listItem = new QListWidgetItem(data);
    listItem->setSizeHint(QSize(60, 25));  // use to change the height
    listItem->setForeground(QBrush(QColor(R,G,B)));

    m_pQListWidget->insertItem(m_pQListWidget->count(), listItem);
    m_pQListWidget->scrollToBottom();

    return true;
}

bool MainWindow::showLog(QString data)
{
    QListWidgetItem *listItem = new QListWidgetItem(data);

    m_pQListWidget->insertItem(m_pQListWidget->count(), listItem);
    m_pQListWidget->scrollToBottom();

    return true;
}

void MainWindow::ItemDoubleClick(QListWidgetItem* item)
{
    item->setFlags(item->flags() | Qt::ItemIsEditable);
}

void MainWindow::buttonVersion()
{
    QMessageBox::information(NULL, "Version", "hjfang\n1.0.0.1");
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

void MainWindow::buttonSaveLog()
{
   QString fileName = QFileDialog::getSaveFileName(
            this,
            tr("select a file."),
            QString().asprintf("%s\\log.txt",qApp->applicationDirPath().toStdString().c_str()),
            tr("log(*.txt);All files(*.*)"));

   QFile file(fileName);
   bool bOpen=file.open(QIODevice::ReadWrite|QIODevice::Truncate|QIODevice::Text);
   if (!bOpen)
   {
       showLog("save to file Error,openfile error");
       return;
   }

   for (int j = 0; j < m_pQListWidget->count(); j++)
   {
       QString itemText = m_pQListWidget->item(j)->text() + "\n";
       file.write(itemText.toStdString().c_str());
   }
   file.close();
}

void MainWindow::buttonClearLog()
{
    m_pQListWidget->clear();
}
