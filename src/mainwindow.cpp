#include "mainwindow.h"
#include "ui_mainwindow.h"

/**
 * @brief MainWindow::MainWindow
 * @param parent
 */
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
    ui->radiusLabel->setToolTip("unit: mile");
    ui->massLabel->setToolTip("unit: kg");
    ui->rotLabel->setToolTip("unit: mile");
    ui->revLabel->setToolTip("unit: mile");
}

/**
 * @brief MainWindow::~MainWindow
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::InitDataTime
 */
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

/**
 * @brief MainWindow::updateDateTime
 */
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

/**
 * @brief MainWindow::updateData
 * update the data of objects
 */
void MainWindow::updateData(){
    if (ui->openGLWidget->getCurrentObject()->getName() == "Sun")
        ui->revolutionEdit->setReadOnly(true);
    else
        ui->revolutionEdit->setReadOnly(false);

    ui->dataName->setText(QString::fromStdString(ui->openGLWidget->getCurrentObject()->getName()));
    ui->radiusEdit->setText(QString::number(ui->openGLWidget->getCurrentObject()->getRadius()));
    ui->massEdit->setText(QString::number(ui->openGLWidget->getCurrentObject()->getMass()));
    ui->rotationEdit->setText(QString::number(3.6/ui->openGLWidget->getCurrentObject()->getSpeedRotation()));
    if (ui->openGLWidget->getCurrentObject()->getName() == "Sun")
        ui->revolutionEdit->setText("0");
    else
        ui->revolutionEdit->setText(QString::number(3.6/ui->openGLWidget->getCurrentObject()->getSpeedRevolution()));
}

/**
 * @brief MainWindow::on_startButton_clicked
 * to start or stop the simulation
 */
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

/**
 * @brief MainWindow::on_hour_valueChanged
 * @param arg1: input to set hour
 */
void MainWindow::on_hour_valueChanged(int arg1)
{
    hour = arg1;
    dateTime->setTime(QTime(hour,minute,second));
}

/**
 * @brief MainWindow::on_minute_valueChanged
 * @param arg1: input to set minute
 */
void MainWindow::on_minute_valueChanged(int arg1)
{
    minute = arg1;
    dateTime->setTime(QTime(hour,minute,second));
}

/**
 * @brief MainWindow::on_second_valueChanged
 * @param arg1: input to set second
 */
void MainWindow::on_second_valueChanged(int arg1)
{
    second = arg1;
    dateTime->setTime(QTime(hour,minute,second));
}

/**
 * @brief MainWindow::on_year_textChanged
 * @param arg1: input to set year
 */
void MainWindow::on_year_textChanged(const QString &arg1)
{
    year = arg1.toInt();
    dateTime->setDate(QDate(year,month,day));
    on_month_currentTextChanged(QString::number(month));
}

/**
 * @brief MainWindow::on_month_currentTextChanged
 * @param arg1: input to set month
 */
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


/**
 * @brief MainWindow::on_timeSpeedSlider_sliderMoved
 * @param position: input to set time speed
 */
void MainWindow::on_timeSpeedSlider_sliderMoved(int position)
{
    if (position == 0)
        ui->timeSpeedLabel->setText("Stop");
    else if (position > -24 && position < 24 ){
        ui->timeSpeedLabel->setText(QString::number(position) + " hour / sec");
        ui->openGLWidget->timeSpeed = position;
    }
    else if (position >= 24 && position < 54){
        ui->timeSpeedLabel->setText(QString::number(position - 23) + " day / sec");
        ui->openGLWidget->timeSpeed = (position - 23) * 24;
    }
    else if (position > -54 && position <= -24){
        ui->timeSpeedLabel->setText(QString::number(position + 23) + " day / sec");
        ui->openGLWidget->timeSpeed = (position + 23) * 24;
    }
    else if (position >= 54 && position < 78){
        ui->timeSpeedLabel->setText(QString::number((position - 54)/2.0) + " month / sec");
        ui->openGLWidget->timeSpeed = (position - 53) * 24 * 30;
    }
    else if (position > -78 && position <= -54){
        ui->timeSpeedLabel->setText(QString::number((position + 54)/2.0) + " month / sec");
        ui->openGLWidget->timeSpeed = (position + 53) * 24 * 30;
    }
    else if (position == 78){
        ui->timeSpeedLabel->setText(" +1 year / sec");
        ui->openGLWidget->timeSpeed = 24 * 365;
    }
    else{
        ui->timeSpeedLabel->setText(" -1 year / sec");
        ui->openGLWidget->timeSpeed = -24 * 365 ;
    }
}

/**
 * @brief MainWindow::on_timeSpeedSlider_valueChanged
 * @param value: input to set time speed
 */
void MainWindow::on_timeSpeedSlider_valueChanged(int value)
{
    if (value == 0)
        ui->timeSpeedLabel->setText("Stop");
    else if (value > -24 && value < 24 ){
        ui->timeSpeedLabel->setText(QString::number(value) + " hour / sec");
        ui->openGLWidget->timeSpeed = value;
    }
    else if (value >= 24 && value < 54){
        ui->timeSpeedLabel->setText(QString::number(value - 23) + " day / sec");
        ui->openGLWidget->timeSpeed = (value - 23) * 24;
    }
    else if (value > -54 && value <= -24){
        ui->timeSpeedLabel->setText(QString::number(value + 23) + " day / sec");
        ui->openGLWidget->timeSpeed = (value + 23) * 24;
    }
    else if (value >= 54 && value < 78){
        ui->timeSpeedLabel->setText(QString::number((value - 54)/2.0) + " month / sec");
        ui->openGLWidget->timeSpeed = (value - 53) * 24 * 30;
    }
    else if (value > -78 && value <= -54){
        ui->timeSpeedLabel->setText(QString::number((value + 54)/2.0) + " month / sec");
        ui->openGLWidget->timeSpeed = (value + 53) * 24 * 30;
    }
    else if (value == 78){
        ui->timeSpeedLabel->setText(" +1 year / sec");
        ui->openGLWidget->timeSpeed = 24 * 365;
    }
    else{
        ui->timeSpeedLabel->setText(" -1 year / sec");
        ui->openGLWidget->timeSpeed = -24 * 365 ;
    }
}

/**
 * @brief MainWindow::on_highlightButton_clicked
 * highlight a selected object and hide the others
 */
void MainWindow::on_highlightButton_clicked()
{
    ui->openGLWidget->is_highlighting = !ui->openGLWidget->is_highlighting;
    if (ui->openGLWidget->is_highlighting){
        for (auto it : ui->openGLWidget->getSolarSystem()->getObjects()){
            if (it->getName() == ui->openGLWidget->getCurrentObject()->getName())
                continue;
            it->setVisibility(false);
        }
    }
    else{
        for (auto it : ui->openGLWidget->getSolarSystem()->getObjects()){
            it->setVisibility(true);
        }
    }
}

/**
 * @brief MainWindow::on_confirmButton_clicked
 * confirm to change parameters
 */
void MainWindow::on_confirmButton_clicked()
{

    GLfloat max_distance = ui->openGLWidget->getSolarSystem()->getObjects()[8]->getDistance();
    GLfloat min_distance = 0.0;

    const QString tx_rad = ui->radiusEdit->text();
    const QString tx_mass = ui->massEdit->text();
    const QString tx_rot = ui->rotationEdit->text();
    const QString tx_rev = ui->revolutionEdit->text();
    QRegExp rx("^([-+]?[0-9]*\.?[0-9]+([eE][-+]?[0-9]+)?)$");
    if (rx.indexIn(tx_rad) != -1){
        if (tx_rad.toFloat() > max_distance || tx_rad.toFloat() < min_distance){
            error_2(min_distance, max_distance);
        }
        else
            ui->openGLWidget->getCurrentObject()->setRadius(tx_rad.toFloat());
    }
    else{
        error_1();
    }

    if (rx.indexIn(tx_mass) != -1){
        ui->openGLWidget->getCurrentObject()->setMass(ui->massEdit->text().toFloat());
    }
    else{
        error_1();
    }

    if (rx.indexIn(tx_rot) != -1){
        ui->openGLWidget->getCurrentObject()->setSpeedRotation(3.6/tx_rot.toFloat());
    }
    else{
        error_1();
    }

    if (rx.indexIn(tx_rev) != -1){
        if (ui->openGLWidget->getCurrentObject()->getName() != "Sun")
            ui->openGLWidget->getCurrentObject()->setSpeedRevolution(3.6/tx_rev.toFloat());
    }
    else{
        error_1();
    }
}

/**
 * @brief MainWindow::on_resetButton_clicked
 * confirm to reset parameters
 */
void MainWindow::on_resetButton_clicked()
{
    int i = 0;
    for (auto it : ui->openGLWidget->objects_copy){
        ui->openGLWidget->getSolarSystem()->getObjects()[i]->setRadius(it.getRadius());
        ui->openGLWidget->getSolarSystem()->getObjects()[i]->setMass(it.getMass());
        ui->openGLWidget->getSolarSystem()->getObjects()[i]->setSpeedRotation(it.getSpeedRotation());
        ui->openGLWidget->getSolarSystem()->getObjects()[i]->setSpeedRevolution(it.getSpeedRevolution());
        i++;
    }
    updateData();
}

/**
 * @brief MainWindow::on_radiusEdit_returnPressed
 * confirm radius changed
 */
void MainWindow::on_radiusEdit_returnPressed()
{
    on_confirmButton_clicked();
}

/**
 * @brief MainWindow::on_massEdit_returnPressed
 * confirm mass changed
 */
void MainWindow::on_massEdit_returnPressed()
{
    on_confirmButton_clicked();
}

/**
 * @brief MainWindow::on_rotationEdit_returnPressed
 * confirm rotation speed changed
 */
void MainWindow::on_rotationEdit_returnPressed()
{
    on_confirmButton_clicked();
}

/**
 * @brief MainWindow::on_revolutionEdit_returnPressed
 * confirm revolution speed changed
 */
void MainWindow::on_revolutionEdit_returnPressed()
{
    on_confirmButton_clicked();
}

/**
 * @brief MainWindow::error_1
 * message box for invalid input
 */
void MainWindow::error_1(){
    QMessageBox msgBox;
    msgBox.setWindowTitle(tr("input error"));
    msgBox.setFixedSize(QSize(300,100));
    msgBox.setText(tr("Input must be real numbers!"));
    msgBox.setInformativeText(tr("please re-enter your parameters"));
    msgBox.exec();
}

/**
 * @brief MainWindow::error_2
 * message box for range error
 * @param min: minimum value to accept
 * @param max: maximum value to accept
 */
void MainWindow::error_2(float min, float max){
    QMessageBox msgBox;
    msgBox.setWindowTitle(tr("range error"));
    msgBox.setFixedSize(QSize(300,100));
    msgBox.setText("input for radius must between " + QString::number(min) + " and " + QString::number(max));
    msgBox.setInformativeText(tr("please re-enter your parameters"));
    msgBox.exec();
}
