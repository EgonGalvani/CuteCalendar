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
#include <unordered_map>
#include <QTimer>

#include "Model/model.h"
#include "eventwidget.h"
#include "msgscheduler.h"

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
    void onModifiedEvent(Model::It);

protected:
    void closeEvent(QCloseEvent *event);

private:
    // Model
    Model model;

    // Scheduler for messages to show to use r
    MsgScheduler *scheduler;

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
    void checkAndAddMemo(Event* e);

    static EventWidget* createEventWidget(const Model::It&, QListWidget* = nullptr);

private slots:
    void ontimeout(std::string);
};

#endif // MAINWINDOW_H
