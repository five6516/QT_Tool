#include "MainWindow.h"
#include <QApplication>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

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
