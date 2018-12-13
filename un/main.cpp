#include "mainwindow.h"
#include "nehewidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    bool fs = false;
    QApplication a(argc, argv);
    MainWindow w;

    w.show();
    return a.exec();
}
