#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QMenu>
#include <QCalendarWidget>
#include <QGroupBox>
#include <QTableView>
#include <QGridLayout>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    //Elementi addCalendar
    QGroupBox *calendarBlock;
    QGridLayout *calendarLayout;
    QCalendarWidget *calendar;

    //Elementi addEventBox
    QGroupBox *eventBlock;
    QGridLayout *eventLayout;
    void addCalendar();
    void addEventBox();

};

#endif // MAINWINDOW_H
