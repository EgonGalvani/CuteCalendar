#include "mainwindow.h"
#include "mycalendar.h"
#include "newevent.h"

#include <QFile>
#include <QTableView>
#include <QGridLayout>
#include <QColor>
#include "eventwidget.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    initCalendarBox();
    initInfoBox();

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(calendarBlock);
    layout->addWidget(infoBlock);
    setMinimumSize(QSize(900,500));
    setLayout(layout);
}

void MainWindow::initCalendarBox() {
    calendarBlock = new QGroupBox(QString("Calendar"));
    calendar = new MyCalendar();

    calendar->setGridVisible(true);
    calendar->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    calendar->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);

    connect(calendar, SIGNAL(selectionChanged()),this , SLOT(selectedDateChanged()));

    QGridLayout *calendarLayout = new QGridLayout;
    calendarLayout->addWidget(calendar, 0, 0);
    calendarBlock->setLayout(calendarLayout);
}

void MainWindow::initInfoBox() {
    infoBlock = new QGroupBox(QString("Info"));

    // init selected date label
    selectedDateLabel = new QLabel(QString("Selected date: ")
        .append(calendar->selectedDate().toString("dd/MM/yyyy")));
    selectedDateLabel->setAlignment(Qt::AlignCenter);
    selectedDateLabel->setFont(QFont("Lato", 13, QFont::Bold));

    // init preview list
    eventList = new QListWidget();
    for(unsigned int i = 0; i < 10; i++) {
        QListWidgetItem *item =
            new EventWidget(QString("ciao"), QIcon(":/res/birthday.png"), "Compleanno Valton", eventList);
        item->setBackgroundColor(QColor(255, 204, 179));
        eventList->addItem(item);
    }

    eventList->setSpacing(6);
    eventList->setIconSize(QSize(64, 64));
    connect(eventList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(showEventDetailsDialog(QListWidgetItem*)));

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
        QMessageBox::information(
        this,
        tr("Application Name"),
        currentEvent->getInfo());
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

    // caricare eventi del giorno date
}
