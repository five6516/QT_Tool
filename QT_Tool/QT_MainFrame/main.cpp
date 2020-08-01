#include "MainWindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle(QStyleFactory::create("Fusion"));
    a.setStyleSheet(QString(R"(
                QPushButton {
                    border-radius: 5px;
                    border-width: 1px;
                    border-color: #1ABC9B;
                    border-style: solid;
                    margin: 0px;
                    padding: 3px;
                    font-size: %1px;
                    color: black;
                    background: white;
                    outline: none;
                }
                QPushButton:hover {
                    outline: none;
                    background: #1ABC9B;
                    color: white;
                    text-decoration:underline;
                }
                )").arg(15));


    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    QDesktopWidget* desk = QApplication::desktop();
    MainWindow w;
    int width = desk->width()*2/3;
    int height = desk->height()*2/3;
    int ax = desk->width()/2 - width/2;
    int ay = desk->height()/2 - height/2;
    w.setGeometry(ax,ay,width,height);
    w.show();

    return a.exec();
}
