#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QWidget(parent){
        addCalendar();
        addEventBox();
        QGridLayout *layout = new QGridLayout;
        layout->addWidget(calendarBlock, 0, 0);
        layout->addWidget(eventBlock,0,1);
        setMinimumSize(QSize(900,500));
        setLayout(layout);
        calendarLayout->setRowMinimumHeight(0, calendar->sizeHint().height());
        calendarLayout->setColumnMinimumWidth(0, calendar->sizeHint().width());
}



MainWindow::~MainWindow()
{


}

void MainWindow::addCalendar()
{
        calendarBlock = new QGroupBox(tr("Calendar"));
        calendar = new QCalendarWidget;
      //  calendar->setMinimumDate(QDate(1900, 1, 1));
      //  calendar->setMaximumDate(QDate(3000, 1, 1));
        calendar->setGridVisible(true);
        calendar->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
        calendar->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);

       // connect(calendar, &QCalendarWidget::currentPageChanged, this , &MainWindow::seeEvent );

        calendarLayout = new QGridLayout;
        calendarLayout->addWidget(calendar, 0, 0);
        calendarBlock->setLayout(calendarLayout);


}

void MainWindow::addEventBox()
{
        eventBlock = new QGroupBox(tr("Eventi"));
        eventLayout= new QGridLayout;
        eventLayout->setAlignment(Qt::AlignTop);

        currentDateEdit = new QDateEdit;
        currentDateEdit->setDisplayFormat("dd MM yyyy");
        currentDateEdit->setDate(calendar->selectedDate());
        currentDateEdit->setDateRange(calendar->minimumDate(),
                                      calendar->maximumDate());
        currentDateEdit->setFixedSize(QSize(100,20));

        currentDateLabel = new QLabel(tr("Current Date"));
        currentDateLabel->setBuddy(currentDateEdit);

        addEvent= new QPushButton(tr("Add Event"));


        connect(currentDateEdit, &QDateEdit::dateChanged,
                calendar, &QCalendarWidget::setSelectedDate);

        connect(calendar, &QCalendarWidget::selectionChanged, this , &MainWindow::selectedDateChanged);

        connect(addEvent, &QPushButton::clicked, this, &MainWindow::addNewEvent);
        eventLayout->addWidget(currentDateLabel, 1, 0);
        eventLayout->addWidget(currentDateEdit, 1, 1);
        eventLayout->addWidget(addEvent);

        eventBlock->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
        eventBlock->setLayout(eventLayout);


}




void MainWindow::selectedDateChanged()
{
    currentDateEdit->setDate(calendar->selectedDate());
}

void MainWindow::addNewEvent()
{
    QWidget * popup = new QWidget();
    popup->show();
    eventLayout->addWidget(new QLabel(tr("Prova")));

}

void MainWindow::addMenu()
{

}


void MainWindow::seeEvent(){

}







