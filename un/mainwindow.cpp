#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "nehewidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //ui->setupUi(this);
    w = new NeHeWidget(this);
//    setCentralWidget(w);
    setGeometry(300,150,800,600);
}

MainWindow::~MainWindow()
{
    delete ui;
}
