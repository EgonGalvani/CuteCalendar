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
    : QWidget(parent) {

    // caricamento dati da file
    try { model.loadFromFile(); }
    catch(std::exception& e) { std::cout << e.what(); }

    // scheduler di messaggi
    connect(&scheduler, SIGNAL(timeout(std::string)),
            this, SLOT(ontimeout(std::string)));

    // aggiungo un memo per ogni evento con avviso del giorno corrente
    for(auto it : model.getEvents(QDate::currentDate()))
        checkAndAddMemo(&**it);

    // init grafica
    calendarBlock = new QGroupBox(QString("Calendar"));
    calendar = new MyCalendar(&model,this);
    infoBlock = new QGroupBox(QString("Info"));
    initCalendarBox();
    initInfoBox();
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(calendarBlock);
    layout->addWidget(infoBlock);
    setMinimumSize(QSize(900,500));
    setLayout(layout);
}

// inizializzazione grafica della parte della view che mostra il calendario
void MainWindow::initCalendarBox() {
    calendar->setGridVisible(true);
    calendar->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    calendar->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);

    connect(calendar, SIGNAL(selectionChanged()),this , SLOT(selectedDateChanged()));

    QGridLayout *calendarLayout = new QGridLayout;
    calendarLayout->addWidget(calendar, 0, 0);
    calendarBlock->setLayout(calendarLayout);
}

// inizializzazione grafica della parte della view che mostra la lista
// di eventi presenti nel giorno selezionato
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

// mostra un dialog che permette la visualizzazione e modifica dei dettagli
// di un specifico evento
void MainWindow::showEventDetailsDialog(QListWidgetItem *it) {

    if(dynamic_cast<EventWidget*>(it)) { // controllo che l'evento considerato sia valido
        Model::It currentIterator = (dynamic_cast<EventWidget*>(it))->getData();

        try {
            // creo e mostro il dialog
            ModifyDialog* modifyDialog = new ModifyDialog(calendar->selectedDate(), currentIterator);
            connect(modifyDialog, SIGNAL(deleteEvent(Model::It)) , this , SLOT(deleteEvent(Model::It)));
            connect(modifyDialog, SIGNAL(modifiedEvent(Model::It)), this , SLOT(onModifiedEvent(Model::It)));
            modifyDialog->exec();
        } catch(std::exception& e) {
            QMessageBox::critical(this, QString("Error"), QString::fromStdString(e.what()));
        }
    } else
        QMessageBox::critical(this, QString("Error"), QString("Error no valid type of ViewCreated"));
}

// richiede al model di eliminare un evento e aggiorna di conseguenza la view
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
        scheduler.clear();
        for(auto e : model.getEvents(QDate::currentDate()))
            checkAndAddMemo(&**e);
    }
}

// vengono aggiornate le informazioni mostrate all'utente
// (poichè è cambiato il giorno selezionato, dovranno essere visualizzati gli eventi di quel giorno)
void MainWindow::selectedDateChanged() {
    // aggiornamento label
    selectedDateLabel->setText(QString("Selected date: ")
        .append(calendar->selectedDate().toString("dd/MM/yyyy")));

    // aggiornamento lista
    refreshList(calendar->selectedDate());
}

// viene mostrato un dialog che permette l'inserimento di un nuovo evento
void MainWindow::showAddEventDialog() {
    NewEventDialog* addEventDialog = new NewEventDialog(calendar->selectedDate());
    connect(addEventDialog, SIGNAL(newEventCreated(Event*)), this, SLOT(insertEvent(Event*)));
    addEventDialog->exec();
}

// inserisco un nuovo evento nel model, aggiorno la lista di elementi mostrati nel calendar
// e in caso anche la lista degli avvisi
void MainWindow::insertEvent(Event *e) {
    // inserisco l'evento nel model
    auto it = model.insertEvent(e);

    // viene inserito in coda un nuovo elmento
    eventList->addItem(createEventWidget(it));

    // ottengo l'evento appena inserito direttamente dall'iteratore
    Event* event = &**it;
    if(event->getDate() == QDate::currentDate())
        checkAndAddMemo(event);
}

// controlla che l'evento passato sia di tipo alert e di conseguenza
// inserisce degli avvisi nello scheduler
void MainWindow::checkAndAddMemo(Event *e) {
    Alert* currentAlert = dynamic_cast<Alert*>(e);
    if(currentAlert) {
        int diff = QTime::currentTime().msecsTo(currentAlert->getAlertTime());
        if(diff > 0) {
            scheduler.addMsg("L'evento " + e->getName() + " sta per iniziare", diff);

            if(currentAlert->doesRepeat()) {
                scheduler.addMsg("Manca sempre meno all'inizio dell'evento " + e->getName(), diff + 5*60*1000);
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
    Event* currentEvent = &**it; // ottengo direttamente l'evento dall'iteratore

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

void MainWindow::onModifiedEvent(Model::It it) {

    // aggiorno la lista degli eventi mostrati nel giorno selezionato
    if((*it)->getDate() == calendar->selectedDate())
        refreshList(calendar->selectedDate());

    // se il giorno dell'evento è quello corrente, controllo se l'evento
    // prevede di mostrare degli avvisi all'utente e in questo caso li aggiorno
    if((*it)->getDate() == QDate::currentDate() && dynamic_cast<Alert*>(&**it)) {
        scheduler.clear();

        for(auto it : model.getEvents(QDate::currentDate()))
            checkAndAddMemo(&**it);
    }
}

// alla chiusura dell'applicativo (e quindi della mainwindow) esso si occuperà di
// salvare tutte le informazioni del model in un file, in modo che esse
// possano essere caricate correttamente alla prossima esecuzione
void MainWindow::closeEvent(QCloseEvent *event) {
    model.saveInFile();
}
