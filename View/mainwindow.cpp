#include <QFile>
#include <QTableView>
#include <QGridLayout>
#include <QColor>
#include <QMessageBox>
#include <stdexcept>
#include <QCloseEvent>
#include <QDate>
#include <QTime>

#include "mainwindow.h"
#include "mycalendar.h"
#include "neweventdialog.h"

#include "modifydialog.h"

#include "eventwidget.h"

#include "../Model/Hierarchy/birthday.h"
#include "../Model/Hierarchy/meeting.h"
#include "../Model/Hierarchy/reminder.h"
#include "../Model/Hierarchy/todolist.h"
#include "../Model/Hierarchy/workout.h"
#include "../Model/Hierarchy/alert.h"
#include "../Model/Hierarchy/eventwithduration.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent),
      calendarBlock(new QGroupBox(QString("Calendar"))),
      calendar(new MyCalendar(&model,this)),
      infoBlock(new QGroupBox(QString("Info"))) {

    // caricamento dati da file
    try { model.loadFromFile(); }
    catch(std::exception& e) { std::cout << e.what(); }
    catch(...) { std::cout << "Eccezione" << std::endl; }

    // init grafica
    initCalendarBox();
    initInfoBox();

    // init timer per avviso eventi
    QTimer *timer = new QTimer(this);
    timer->setInterval(1000*60);
    connect(timer, SIGNAL(timeout()), this, SLOT(ontimerout()));
    timer->start();

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

        try {
            ModifyDialog* modifyDialog = new ModifyDialog(calendar->selectedDate(),currentIterator);
            connect(modifyDialog, SIGNAL(deleteEvent(Model::It)) , this , SLOT(deleteEvent(Model::It)));
            modifyDialog->exec();
        } catch(std::exception& e) {
            QMessageBox::critical(this, QString("Error"), QString::fromStdString(e.what()));
        }
    } else
        QMessageBox::critical(this, QString("Error"), QString("Error no valid type of ViewCreated"));
}

void MainWindow::deleteEvent(Model::It it) {
    try {
        model.removeEvent(it);
        QMessageBox::information(this, QString("Success"), QString("Evento rimosso con successo"));
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
    NewEventDialog* addEventDialog = new NewEventDialog(calendar->selectedDate());
    connect(addEventDialog, SIGNAL(newEventCreated(Event*)), this, SLOT(insertEvent(Event*)));
    addEventDialog->exec();
}

void MainWindow::insertEvent(Event *e) {
    // inserisco l'evento
    auto it = model.insertEvent(e);
    eventList->addItem(createEventWidget(it));
}

void MainWindow::refreshList(const QDate& date) {
    eventList->clear();

    for(auto it : model.getEvents(date))
        eventList->addItem(createEventWidget(it));
}

EventWidget* MainWindow::createEventWidget(const Model::It& it, QListWidget *parent) {
    Event* currentEvent = &**it;

    // evento di default -> birthday
    QIcon eventIcon = QIcon(":/res/birthday.png");
    QColor widgetColor = QColor(Qt::green);

    if(dynamic_cast<Meeting*>(currentEvent)) {
        eventIcon = QIcon(":/res/meeting.jpg");
        widgetColor = QColor(Qt::yellow);
    } else if(dynamic_cast<Reminder*>(currentEvent)) {
        eventIcon = QIcon(":/res/reminder.png");
        widgetColor = QColor(Qt::cyan);
    } else if(dynamic_cast<ToDoList*>(currentEvent)) {
        eventIcon = QIcon(":/res/todolist.png");
        widgetColor = QColor(Qt::green);
    } else {
        eventIcon = QIcon(":/res/workout.jpg");
        widgetColor = QColor(Qt::lightGray);
    }

    EventWidget* e = new EventWidget(it, eventIcon, parent);
    e->setBackgroundColor(widgetColor);
    return e;
}


void MainWindow::ontimerout() {

    for(auto it : model.getEvents(QDate::currentDate())) {
        Alert* currentAlert = dynamic_cast<Alert*>(&**it);
        if(currentAlert) {
           int diff = QTime::currentTime().secsTo(currentAlert->getAlertTime());

           if(diff > 0 && diff <= 60) {
                QMessageBox* alertMsg = new QMessageBox(this);
                alertMsg->setText(QString("L'evento ") + QString::fromStdString(currentAlert->getName()) + QString(" sta per iniziare!"));
                alertMsg->setInformativeText("success");
                alertMsg->setModal(false);
                alertMsg->show();
           }

           EventWithDuration* eventWithDuration = dynamic_cast<EventWithDuration*>(&**it);
           if(currentAlert->doesRepeat() && eventWithDuration) {
               diff = QTime::currentTime().secsTo(eventWithDuration->getStartTime());

               if(diff > 0 && diff <= 60) {
                   QMessageBox* startMsg = new QMessageBox(this);
                   startMsg->setText(QString("L'evento ") + QString::fromStdString(currentAlert->getName()) + QString(" è iniziato!"));
                   startMsg->setInformativeText("success");
                   startMsg->setModal(false);
                   startMsg->show();
               }
           }
        }
    }
}

void MainWindow::closeEvent(QCloseEvent *event) {
    model.saveInFile();
}
