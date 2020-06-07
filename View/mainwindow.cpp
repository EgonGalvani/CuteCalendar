#include <QFile>
#include <QTableView>
#include <QGridLayout>
#include <QColor>
#include <QMessageBox>
#include <stdexcept>
#include <QCloseEvent>
#include <QDate>
#include <QTime>

#include "msgscheduler.h"
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

    // scheduler di messaggi
    scheduler = new MsgScheduler(this);
    connect(scheduler, SIGNAL(timeout(std::string)),
            this, SLOT(ontimeout(std::string)));

    // aggiungo un memo per ogni evento con avviso del giorno corrente
    for(auto it : model.getEvents(QDate::currentDate()))
        checkAndAddMemo(&**it);

    // init grafica
    initCalendarBox();
    initInfoBox();

    QHBoxLayout *layout = new QHBoxLayout(this);
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
    eventList = new QListWidget(this);
    eventList->setSpacing(6);
    eventList->setIconSize(QSize(64, 64));
    connect(eventList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(showEventDetailsDialog(QListWidgetItem*)));
    refreshList(calendar->selectedDate()); // aggiungo gli eventi della data corrente

    // init add event button
    addEventBtn = new QPushButton(tr("Add Event"),this);
    connect(addEventBtn, SIGNAL(clicked(bool)), this, SLOT(showAddEventDialog()));

    // aggiungo gli elementi al layout
    QVBoxLayout *infoLayout = new QVBoxLayout(this);
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
        Model::It currentIterator = (dynamic_cast<EventWidget*>(it))->getData();

        try {
            ModifyDialog* modifyDialog = new ModifyDialog(calendar->selectedDate(), currentIterator);
            connect(modifyDialog, SIGNAL(deleteEvent(Model::It)) , this , SLOT(deleteEvent(Model::It)));
            modifyDialog->exec();
        } catch(std::exception& e) {
            QMessageBox::critical(this, QString("Error"), QString::fromStdString(e.what()));
        }
    } else
        QMessageBox::critical(this, QString("Error"), QString("Error no valid type of ViewCreated"));
}

void MainWindow::deleteEvent(Model::It it) {

    // ottengo informazioni relative all'evento prima che questo venga eliminato
    bool isAlert = dynamic_cast<Alert*>(&**it);
    bool isToday = (**it).getDate() == QDate::currentDate();

    // elimino dal model l'elemento considerato
    try {
        model.removeEvent(it);
        QMessageBox::information(this, QString("Success"), QString("Evento rimosso con successo"));
    } catch(...) {
        QMessageBox::critical(this, QString("Error"), QString("Error deleting element"));
    }

    // aggiorno la lista di eventi mostrata nel calendar
    refreshList(calendar->selectedDate());

    // se l'evento eliminato aveva dei memo allora li aggiorno
    if(isAlert && isToday) {
        scheduler->clear();
        for(auto e : model.getEvents(QDate::currentDate()))
            checkAndAddMemo(&**e);
    }
}

void MainWindow::selectedDateChanged() {
    // aggiornamento label
    selectedDateLabel->setText(QString("Selected date: ")
        .append(calendar->selectedDate().toString("dd/MM/yyyy")));

    // aggiornamento lista
    refreshList(calendar->selectedDate());
}

// mostro il dialog di inserimento di un evento
void MainWindow::showAddEventDialog() {
    NewEventDialog* addEventDialog = new NewEventDialog(calendar->selectedDate());
    connect(addEventDialog, SIGNAL(newEventCreated(Event*)), this, SLOT(insertEvent(Event*)));
    addEventDialog->exec();
}

// inserisco un nuovo evento nel model, aggiorno la lista di elementi mostrati nel calendar
// e in caso anche la lista degli avvisi
void MainWindow::insertEvent(Event *e) { // TODO: controlla gestione memoria nell'insert
    // inserisco l'evento nel model
    auto it = model.insertEvent(e);

    // viene inserito in coda un nuovo elmento
    eventList->addItem(createEventWidget(it));

    if(e->getDate() == QDate::currentDate())
        checkAndAddMemo(e);
}

// controlla che l'evento passato sia di tipo alert e di conseguenza
// inserisce degli avvisi nello scheduler
void MainWindow::checkAndAddMemo(Event *e) {
    Alert* currentAlert = dynamic_cast<Alert*>(e);
    if(currentAlert) {
        int diff = QTime::currentTime().msecsTo(currentAlert->getAlertTime());
        if(diff > 0) {
            scheduler->addMsg("L'evento " + e->getName() + " sta per iniziare", diff);

            if(currentAlert->doesRepeat()) {
                scheduler->addMsg("Manca sempre meno all'inizio dell'evento " + e->getName(),
                                    diff + 5*60*1000);
            }
        }
    }
}

// fa il refresh della lista di eventi mostrati nel calendar
void MainWindow::refreshList(const QDate& date) {
    eventList->clear();

    for(auto it : model.getEvents(date))
        eventList->addItem(createEventWidget(it));
}

// crea un widget adeguato a seconda dell'evento considerato (il widget verrà utilizzato
// per essere mostrato nella lista di eventi del calendario
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

// quando un avviso deve essere mostrato, lo scheduler emette un signal,
// che viene ricevuto da questo slot, che si occupa di mostrare l'avviso
void MainWindow::ontimeout(std::string msg) {
    QMessageBox* alertMsg = new QMessageBox(this);
    alertMsg->setText(QString::fromStdString(msg));
    alertMsg->setInformativeText("success");
    alertMsg->setModal(false);
    alertMsg->show();
}

// alla chiusura dell'applicativo esso si occuperà di
// salvare tutte le informazioni del model in un file, in modo che esse
// possano essere caricate correttamente alla prossima esecuzione
void MainWindow::closeEvent(QCloseEvent *event) {
    model.saveInFile();
}
