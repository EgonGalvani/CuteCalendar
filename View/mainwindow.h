#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QCalendarWidget>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>

class MainWindow : public QWidget {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow() = default;
private slots:
    void seeEvent();
    void selectedDateChanged();
    void showAddEventDialog();

private:
    // Elementi Menu
    // QVBoxLayout menu;

    // Elementi calendario
    QGroupBox *calendarBlock;
    QCalendarWidget *calendar;

    // Elementi sezione di destra
    QGroupBox *infoBlock;
    QLabel *currentDateLabel;
    QListWidget *eventPreviewList;
    QPushButton *addEventBtn;

    void addMenu();

    // init calendario principale
    void initCalendar();

    // init sezione di destra
    void initInfoBox();
};

#endif // MAINWINDOW_H
