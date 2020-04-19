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
#include <QDate>
#include <QLabel>
#include <QDateEdit>


class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void seeEvent();
    void selectedDateChanged();

private:
    //Elementi addCalendar
    QGroupBox *calendarBlock;
    QGridLayout *calendarLayout;
    QCalendarWidget *calendar;

    //Elementi addEventBox
    QGroupBox *eventBlock;
    QGridLayout *eventLayout;
    QLabel *currentDateLabel;
    QDateEdit *currentDateEdit;

    void addCalendar();
    void addEventBox();

};

#endif // MAINWINDOW_H
