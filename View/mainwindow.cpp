#include "mainwindow.h"
#include "mycalendar.h"
#include "newevent.h"
#include "viewallenamento.h"
#include "viewcompleanno.h"
#include "viewmeeting.h"
#include "viewpromemoria.h"
#include "modifydialog.h"

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
    : QWidget(parent),
      calendarBlock(new QGroupBox(QString("Calendar"))),
      calendar(new MyCalendar()),
      infoBlock(new QGroupBox(QString("Info"))) {

    // evento di prova
    model.insertEvent(new BirthDay(Date(12, 5, 1999), "Compleanno Valton", "Oggi è il compleanno di valton",
        "Padova",Date(12, 5, 2020) , nullptr));


    Time t1 = Time();
    Time t2 = Time();
    Date d1 = Date(19,2,2020);
    Date d2 = Date(12, 5, 2020);
    std::vector<std::string>* vettoreTag = new std::vector<std::string>();
    vettoreTag->push_back("Fit");
    vettoreTag->push_back("Insta");
    vettoreTag->push_back("ValtonGay");
    model.insertEvent(new Workout(0,t1,t2,"palestra","sollevamento pesi","casa",d1,vettoreTag));

    Time tt1 = Time(10,30,30);
    Time tt2 = Time(12,30,30);
    Time alert = Time(9,30,30);
    Date dd1 = Date();
    std::vector<std::string>* tags = new std::vector<std::string>();
    tags->push_back("Bambino");
    tags->push_back("Scuola");
    tags->push_back("Genitore");
    model.insertEvent(new Reminder(0,tt1,tt2,alert,true,"Figlio","prendere bambino a scuola","Scuola",
                             dd1,tags));

    std::vector<std::string> par = std::vector<std::string>();
    par.push_back("danielegiachetto1999@gmail.com");
    par.push_back("valtontahiraj@gmail.com");
    model.insertEvent(new Meeting(par,tt1,tt2,alert,true,"meet","incontro zoom",
                            "casa",d2,tags));







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
        EventWidget* currentEventWidget = dynamic_cast<EventWidget*>(it);
        Model::It currentIterator = currentEventWidget->getData();
        Event* currentEvent = &**currentIterator;

        ModifyDialog* currentView = nullptr;

        if(dynamic_cast<BirthDay*>(currentEvent))
            currentView = new ModifyDialog(currentIterator);
        else if (dynamic_cast<Meeting*>(currentEvent))
            currentView = new ModifyDialog(currentIterator);
        else if(dynamic_cast<Reminder*>(currentEvent))
            currentView = new ModifyDialog(currentIterator);
        else if(dynamic_cast<ToDoList*>(currentEvent))
            currentView = new ModifyDialog(currentIterator);
        else if(dynamic_cast<Workout*>(currentEvent))
            currentView = new ModifyDialog(currentIterator);

        if(!currentView)
            QMessageBox::critical(this, QString("Error"), QString("Nessun tipo della gerarchia identificato"));
        else {
            connect(currentView, SIGNAL(deleteEvent(Model::It)) , this , SLOT(deleteEvent(Model::It)));
            currentView->exec();
        }
    } else
        QMessageBox::critical(this, QString("Error"), QString("Error no valid type of ViewCreated"));
}

void MainWindow::deleteEvent(Model::It it) {
    try {
        model.removeEvent(it);
    } catch(...) {
        QMessageBox::critical(this, QString("Error"), QString("Error deleting element"));
    }

    // gli iteratori non sono più validi a seguito di un'eliminazione
    refreshList(calendar->selectedDate());
}

void MainWindow::selectedDateChanged() {
    // aggiornamento label
    selectedDateLabel->setText(QString("Selected date: ")
        .append(calendar->selectedDate().toString("dd/MM/yyyy")));

    // aggiornamento lista
    refreshList(calendar->selectedDate());
}

void MainWindow::showAddEventDialog() {
    NewEvent* addEventPopup = new NewEvent();
    connect(addEventPopup, SIGNAL(newEventCreated(Event*)), this, SLOT(insertEvent(Event*)));
    addEventPopup->exec();
}

void MainWindow::insertEvent(Event *e) {
    // inserisco l'evento
    model.insertEvent(e); // ritorna l'iteratore all'elemento inserito

    // aggiorno la lista TODO: vedere se aggiugnere semplicemente un elemento alla lista
    refreshList(calendar->selectedDate());
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
