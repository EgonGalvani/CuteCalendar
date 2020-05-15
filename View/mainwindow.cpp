#include "mainwindow.h"
#include "mycalendar.h"
#include "newevent.h"
#include "viewallenamento.h"

#include <QFile>
#include <QTableView>
#include <QGridLayout>
#include <QColor>

#include "eventwidget.h"
#include "eventwidgetbuilder.h"

#include "../Model/Hierarchy/birthday.h"
#include "../Model/Hierarchy/meeting.h"
#include "../Model/Hierarchy/reminder.h"
#include "../Model/Hierarchy/todolist.h"
#include "../Model/Hierarchy/workout.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent), calendarBlock(new QGroupBox(QString("Calendar"))),
        infoBlock(new QGroupBox(QString("Info"))), calendar(new MyCalendar()) {

    // evento di prova
    model.insertEvent(Date(12, 5, 2020), new BirthDay(Date(12, 5, 2020), "Compleanno Valton", "Oggi è il compleanno di valton",
                                                      "Padova", Date(12, 5, 1999), nullptr));

    // eventi di prova...


    initCalendarBox();
    initInfoBox();

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(calendarBlock);
    layout->addWidget(infoBlock);
    setMinimumSize(QSize(900,500));
    setLayout(layout);
}

void MainWindow::initCalendarBox() {
    calendar->setGridVisible(true);
    calendar->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    calendar->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);

    connect(calendar, SIGNAL(selectionChanged()),this , SLOT(selectedDateChanged()));

    QGridLayout *calendarLayout = new QGridLayout;
    calendarLayout->addWidget(calendar, 0, 0);
    calendarBlock->setLayout(calendarLayout);
}

void MainWindow::initInfoBox() {

    // init selected date label
    selectedDateLabel = new QLabel(QString("Selected date: ")
        .append(calendar->selectedDate().toString("dd/MM/yyyy")));
    selectedDateLabel->setAlignment(Qt::AlignCenter);
    selectedDateLabel->setFont(QFont("Lato", 13, QFont::Bold));

    // init preview list
    eventList = new QListWidget();
    eventList->setSpacing(6);
    eventList->setIconSize(QSize(64, 64));
    connect(eventList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(showEventDetailsDialog(QListWidgetItem*)));
    refreshList(calendar->selectedDate()); // aggiungo gli eventi della data corrente

    // init add event button
    addEventBtn = new QPushButton(tr("Add Event"));
    connect(addEventBtn, SIGNAL(clicked(bool)), this, SLOT(showAddEventDialog()));

    // aggiungo gli elementi al layout
    QVBoxLayout *infoLayout = new QVBoxLayout();
    infoLayout->addWidget(selectedDateLabel);
    infoLayout->addWidget(eventList);
    infoLayout->addWidget(addEventBtn);

    // design dell' info block
    infoBlock->setMaximumWidth(400);
    infoBlock->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    infoBlock->setLayout(infoLayout);
}

void MainWindow::showEventDetailsDialog(QListWidgetItem *it) {
    if(dynamic_cast<EventWidget*>(it)) {
        EventWidget* currentEvent = static_cast<EventWidget*>(it);

        // TODO: aggiornamento eventi
    /**    QMessageBox::information(
        this,
        tr("Application Name"),
        "placeholder"); //currentEvent->getInfo());**/
        ViewAllenamento* prova = new ViewAllenamento();
        prova->exec();
    } else
        QMessageBox::critical(this, QString("Error"), QString("Error showing element details"));
}

void MainWindow::selectedDateChanged() {
    // aggiornamento label
    selectedDateLabel->setText(QString("Selected date: ")
        .append(calendar->selectedDate().toString("dd/MM/yyyy")));

    // aggiornamento lista
    refreshList(calendar->selectedDate());
}

void MainWindow::showAddEventDialog() {
    NewEvent* popup = new NewEvent();
    popup->exec();
}

void MainWindow::refreshList(const QDate& date) {
    eventList->clear();

    for(auto it : model.getEvents(date)) {
        Event* currentEvent = &**it;
        if(dynamic_cast<BirthDay*>(currentEvent))
            eventList->addItem(EventWidgetBuilder::buildBirthdayWidget(it, eventList));
        else if(dynamic_cast<Meeting*>(currentEvent))
            eventList->addItem(EventWidgetBuilder::buildMeetingWidget(it, eventList));
        else if(dynamic_cast<Reminder*>(currentEvent))
            eventList->addItem(EventWidgetBuilder::buildReminderWidget(it, eventList));
        else if(dynamic_cast<ToDoList*>(currentEvent))
            eventList->addItem(EventWidgetBuilder::buildTodoListWidget(it, eventList));
        else
            eventList->addItem(EventWidgetBuilder::buildWorkoutWidget(it, eventList));
    }
}
