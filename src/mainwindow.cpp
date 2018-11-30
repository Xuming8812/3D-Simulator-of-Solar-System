#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    updateData();
    isPlay = false;
    timer = new QTimer(this);
    QIcon icon(":icon/play.png");
    ui->startButton->setIcon(icon);
    InitDataTime();
    connect(timer,SIGNAL(timeout()),this,SLOT(updateDateTime()));

    timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitDataTime(){
    dateTime = new QDateTime(QDateTime::currentDateTime());

    QTime time = dateTime->time();
    hour = time.hour();
    minute = time.minute();
    second = time.second();
    ui->hour->setValue(hour);
    ui->minute->setValue(minute);
    ui->second->setValue(second);

    QDate date = dateTime->date();
    year = date.year();
    month = date.month();
    day = date.day();
    ui->day->setCurrentText(QString::number(day, 10));
    ui->month->setCurrentText(QString::number(month, 10));
    ui->year->setText(QString::number(year, 10));
}

void MainWindow::updateDateTime(){

    dateTime = new QDateTime(dateTime->addSecs(1));
    QTime time = dateTime->time();
    hour = time.hour();
    minute = time.minute();
    second = time.second();
    ui->hour->setValue(hour);
    ui->minute->setValue(minute);
    ui->second->setValue(second);

    QDate date = dateTime->date();
    year = date.year();
    month = date.month();
    day = date.day();
    ui->day->setCurrentText(QString::number(day, 10));
    ui->month->setCurrentText(QString::number(month, 10));
    ui->year->setText(QString::number(year, 10));

}

void MainWindow::updateData(){
    ui->dataName->setText(QString::fromStdString(ui->openGLWidget->getCurrentObject()->getName()));
    ui->dataRadius->setText(QString::number(ui->openGLWidget->getCurrentObject()->getRadius()));
    ui->dataRevolution->setText(QString::number(ui->openGLWidget->getCurrentObject()->getSpeedRevolution()));
    ui->dataRotation->setText(QString::number(ui->openGLWidget->getCurrentObject()->getSpeedRotation()));
}

void MainWindow::on_zoomInButton_clicked()
{
    int curVal = ui->zoomSlider->value();
    if (curVal < 150)
        ui->zoomSlider->setValue(curVal+5);
}

void MainWindow::on_zoomOutButton_clicked()
{
    int curVal = ui->zoomSlider->value();
    if (curVal > 0)
        ui->zoomSlider->setValue(curVal-5);
}

void MainWindow::on_startButton_clicked()
{
    if (!isPlay){
        isPlay = true;
        QIcon icon(":icon/pause.png");
        ui->startButton->setIcon(icon);
    }
    else {
        isPlay = false;
        QIcon icon(":icon/play.png");
        ui->startButton->setIcon(icon);
    }
}

void MainWindow::on_hour_valueChanged(int arg1)
{
    hour = arg1;
    dateTime->setTime(QTime(hour,minute,second));
}

void MainWindow::on_minute_valueChanged(int arg1)
{
    minute = arg1;
    dateTime->setTime(QTime(hour,minute,second));
}

void MainWindow::on_second_valueChanged(int arg1)
{
    second = arg1;
    dateTime->setTime(QTime(hour,minute,second));
}

void MainWindow::on_year_textChanged(const QString &arg1)
{
    year = arg1.toInt();
    dateTime->setDate(QDate(year,month,day));
    on_month_currentTextChanged(QString::number(month));
}

void MainWindow::on_month_currentTextChanged(const QString &arg1)
{
    month = arg1.toInt();
    dateTime->setDate(QDate(year,month,day));

    if(month==1 || month==3 || month==5 || month==7 || month==8 || month==10 || month==12)
        ui->day->setMaxCount(31);
    else if(month==4 || month==6 || month==9 || month==11)
        ui->day->setMaxCount(30);
    else if(QDate::isLeapYear(year) && month == 2)
        ui->day->setMaxCount(29);
    else
        ui->day->setMaxCount(28);
}

void MainWindow::on_day_currentTextChanged(const QString &arg1)
{
    day = arg1.toInt();
    dateTime->setDate(QDate(year,month,day));
}

void MainWindow::on_paramButton_clicked()
{
    paramForm = new ParamForm(this,ui->openGLWidget->getSolarSystem()->getObjects()[1]);
    paramForm->show();
}
