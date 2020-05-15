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

private:
    // Model
    Model model;

    // Elementi Menu
    // QVBoxLayout menu;

    // Elementi calendario
    QGroupBox *calendarBlock;
    QCalendarWidget *calendar;

    // Elementi sezione di destra
    QGroupBox *infoBlock;
    QLabel *selectedDateLabel;
    QListWidget *eventList;
    QPushButton *addEventBtn;

    // void addMenu();

    // init calendario e
    void initCalendarBox();
    void initInfoBox();

    // gestione della lista
    void refreshList(const QDate&);
};

#endif // MAINWINDOW_H
