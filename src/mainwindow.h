#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDate>
#include <QTime>
#include <QTimer>
#include "paramform.h"
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

    void on_zoomInButton_clicked();

    void on_zoomOutButton_clicked();

    void on_startButton_clicked();

    void on_hour_valueChanged(int arg1);

    void on_minute_valueChanged(int arg1);

    void on_second_valueChanged(int arg1);

    void on_year_textChanged(const QString &arg1);

    void on_month_currentTextChanged(const QString &arg1);

    void on_day_currentTextChanged(const QString &arg1);

    void on_paramButton_clicked();

private:
    Ui::MainWindow *ui;
    ParamForm *paramForm;
    QTimer *timer;
    bool isPlay;


    QDateTime *dateTime;
    int year, month, day;
    int hour, minute, second;
};

#endif // MAINWINDOW_H
