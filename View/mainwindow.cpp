#include "mainwindow.h"
#include "mycalendar.h"
#include "newevent.h"

#include <QFile>
#include <QTableView>
#include <QGridLayout>
#include <QColor>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    initCalendar();
    initInfoBox();

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(calendarBlock);
    layout->addWidget(infoBlock);
    setMinimumSize(QSize(900,500));
    setLayout(layout);
}

void MainWindow::initCalendar() {
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

    // init current date label
    currentDateLabel = new QLabel(QString("Current date: ")
        .append(calendar->selectedDate().toString("dd/MM/yyyy")));

    // init preview list
    eventPreviewList = new QListWidget();
    QListWidgetItem *item =
            new QListWidgetItem(QIcon(":/res/birthday.png"), "Compleanno Valton", eventPreviewList);
    item->setBackgroundColor(QColor(255, 204, 179));
    eventPreviewList->addItem(item);
    eventPreviewList->setSpacing(8);
    eventPreviewList->setIconSize(QSize(64, 64));

    // init add event button
    addEventBtn = new QPushButton(tr("Add Event"));
    connect(addEventBtn, SIGNAL(clicked(bool)), this, SLOT(showAddEventDialog()));

    // aggiungo gli elementi al layout
    QVBoxLayout *infoLayout = new QVBoxLayout();
    infoLayout->setAlignment(Qt::AlignHCenter);
    infoLayout->addWidget(currentDateLabel);
    infoLayout->addWidget(eventPreviewList);
    infoLayout->addWidget(addEventBtn);

    // design dell' info block
    infoBlock->setMaximumWidth(400);
    infoBlock->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    infoBlock->setLayout(infoLayout);
}

void MainWindow::selectedDateChanged() {
    // aggiornamento label
    currentDateLabel->setText(QString("Current date: ")
        .append(calendar->selectedDate().toString("dd/MM/yyyy")));

    // TODO: aggiornamento lista eventi
}

void MainWindow::showAddEventDialog() {
    NewEvent* popup = new NewEvent();
    popup->exec();
}

void MainWindow::addMenu() {

}

void MainWindow::seeEvent() {

}
