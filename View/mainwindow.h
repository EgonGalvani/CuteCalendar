#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QCalendarWidget>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include <QListWidgetItem>

#include "Model/model.h"

class MainWindow : public QWidget {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow() = default;

private slots:
    void selectedDateChanged();
    void showAddEventDialog();
    void showEventDetailsDialog(QListWidgetItem*);
    void deleteEvent(Model::It);
    void insertEvent(Event*);

protected:
    void closeEvent(QCloseEvent *event);

private:
    // Model
    Model model;

    // Elementi calendario
    QGroupBox *calendarBlock;
    QCalendarWidget *calendar;

    // Elementi sezione di destra
    QGroupBox *infoBlock;
    QLabel *selectedDateLabel;
    QListWidget *eventList;
    QPushButton *addEventBtn;

    void initCalendarBox();
    void initInfoBox();
    void refreshList(const QDate&);
};

#endif // MAINWINDOW_H
