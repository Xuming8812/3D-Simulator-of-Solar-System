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
    QIcon icon(":icon/pause.png");
    ui->startButton->setIcon(icon);
    InitDataTime();
    connect(timer,SIGNAL(timeout()),this,SLOT(updateDateTime()));
    connect(ui->openGLWidget,SIGNAL(currentObjectChanged()),this,SLOT(updateData()));
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
    ui->radiusEdit->setText(QString::number(ui->openGLWidget->getCurrentObject()->getRadius()));
    ui->massEdit->setText(QString::number(ui->openGLWidget->getCurrentObject()->getMass()));
    ui->revolutionEdit->setText(QString::number(360.0/ui->openGLWidget->getCurrentObject()->getSpeedRevolution()));
    ui->rotationEdit->setText(QString::number(360.0/ui->openGLWidget->getCurrentObject()->getSpeedRotation()));

}

void MainWindow::on_startButton_clicked()
{
    if (!ui->openGLWidget->is_play){
        ui->openGLWidget->is_play = true;
        QIcon icon(":icon/pause.png");
        ui->startButton->setIcon(icon);
        ui->openGLWidget->timer.start(16);
    }
    else {
        ui->openGLWidget->is_play = false;
        QIcon icon(":icon/play.png");
        ui->startButton->setIcon(icon);
        ui->openGLWidget->timer.stop();
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



void MainWindow::on_timeSpeedSlider_sliderMoved(int position)
{
    if (position == 0)
        ui->timeSpeedLabel->setText("Stop");
    else if (position > -24 && position < 24 )
        ui->timeSpeedLabel->setText(QString::number(position) + " hour / sec");
    else if (position >= 24 && position < 54)
        ui->timeSpeedLabel->setText(QString::number(position - 23) + " day / sec");
    else if (position > -54 && position <= -24)
        ui->timeSpeedLabel->setText(QString::number(position + 23) + " day / sec");
    else if (position >= 54 && position < 78)
        ui->timeSpeedLabel->setText(QString::number((position - 54)/2.0) + " month / sec");
    else if (position > -78 && position <= -54)
        ui->timeSpeedLabel->setText(QString::number((position + 54)/2.0) + " month / sec");
    else if (position == 78)
        ui->timeSpeedLabel->setText(" +1 year / sec");
    else
        ui->timeSpeedLabel->setText(" -1 year / sec");
}

void MainWindow::on_timeSpeedSlider_valueChanged(int value)
{
    if (value == 0)
        ui->timeSpeedLabel->setText("Stop");
    else if (value > -24 && value < 24 )
        ui->timeSpeedLabel->setText(QString::number(value) + " hour / sec");
    else if (value >= 24 && value < 54)
        ui->timeSpeedLabel->setText(QString::number(value - 23) + " day / sec");
    else if (value > -54 && value <= -24)
        ui->timeSpeedLabel->setText(QString::number(value + 23) + " day / sec");
    else if (value >= 54 && value < 78)
        ui->timeSpeedLabel->setText(QString::number((value - 54)/2.0) + " month / sec");
    else if (value > -78 && value <= -54)
        ui->timeSpeedLabel->setText(QString::number((value + 54)/2.0) + " month / sec");
    else if (value == 78)
        ui->timeSpeedLabel->setText(" +1 year / sec");
    else
        ui->timeSpeedLabel->setText(" -1 year / sec");
}

void MainWindow::on_highlightButton_clicked()
{
    ui->openGLWidget->is_highlighting = !ui->openGLWidget->is_highlighting;
    if (ui->openGLWidget->is_highlighting){
        for (auto it : ui->openGLWidget->getSolarSystem()->getObjects()){
            if (it->getName() == ui->openGLWidget->getCurrentObject()->getName())
                continue;
            it->setVisibility(false);
//            it->draw();
        }
    }
    else{
        for (auto it : ui->openGLWidget->getSolarSystem()->getObjects()){
            it->setVisibility(true);
//            it->draw();
        }
    }
}



void MainWindow::on_confirmButton_clicked()
{
//    qDebug() << ui->dataRadius->text().toFloat

//    qDebug() << ui->radiusEdit->text();
    ui->openGLWidget->getCurrentObject()->setRadius(ui->radiusEdit->text().toFloat());
    ui->openGLWidget->getCurrentObject()->setMass(ui->massEdit->text().toFloat());
}

void MainWindow::on_resetButton_clicked()
{
    int i = 0;
    for (auto it : ui->openGLWidget->objects_copy){
        ui->openGLWidget->getSolarSystem()->getObjects()[i]->setRadius(it.getRadius());
        i++;
    }
    updateData();
}

void MainWindow::on_radiusEdit_returnPressed()
{
    on_confirmButton_clicked();
}

void MainWindow::on_massEdit_returnPressed()
{
    on_confirmButton_clicked();
}

void MainWindow::on_rotationEdit_returnPressed()
{
    on_confirmButton_clicked();
}

void MainWindow::on_revolutionEdit_returnPressed()
{
    on_confirmButton_clicked();
}
