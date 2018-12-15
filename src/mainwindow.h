#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDate>
#include <QTime>
#include <QTimer>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void InitDataTime();


private slots:
    void updateDateTime();

    void updateData();

//    void on_zoomInButton_clicked();

//    void on_zoomOutButton_clicked();

    void on_startButton_clicked();

    void on_hour_valueChanged(int arg1);

    void on_minute_valueChanged(int arg1);

    void on_second_valueChanged(int arg1);

    void on_year_textChanged(const QString &arg1);

    void on_month_currentTextChanged(const QString &arg1);

    void on_day_currentTextChanged(const QString &arg1);

    void on_timeSpeedSlider_sliderMoved(int position);

    void on_highlightButton_clicked();

    void on_timeSpeedSlider_valueChanged(int value);

    void on_confirmButton_clicked();

    void on_resetButton_clicked();

    void on_radiusEdit_returnPressed();

    void on_massEdit_returnPressed();

    void on_rotationEdit_returnPressed();

    void on_revolutionEdit_returnPressed();

    void error_1();

    void error_2(float min, float max);



private:
    Ui::MainWindow *ui;
    QTimer *timer;
    bool isPlay;


    QDateTime *dateTime;
    int year, month, day;
    int hour, minute, second;

};

#endif // MAINWINDOW_H
