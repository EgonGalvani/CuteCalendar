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
#include <QPushButton>
#include <QScrollArea>


class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void seeEvent();
    void selectedDateChanged();
    void addNewEvent();

private:
    //Elementi Menu
    QVBoxLayout menu;

    //Elementi addCalendar
    QGroupBox *calendarBlock;
    QGridLayout *calendarLayout;
    QCalendarWidget *calendar;

    //Elementi addEventBox
    QGroupBox *eventBlock;
    QVBoxLayout *eventLayout;
    QHBoxLayout *eventLayoutTop;
    QVBoxLayout *eventLayoutBot;
    QScrollArea *areaEventi;
    QLabel *currentDateLabel;
    QDateEdit *currentDateEdit;
    QPushButton *addEvent;

    void addMenu();
    void addCalendar();
    void addEventBox();
};

#endif // MAINWINDOW_H
