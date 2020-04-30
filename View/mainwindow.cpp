#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent){
        addCalendar();
        addEventBox();
        QHBoxLayout *layout = new QHBoxLayout;
        layout->addWidget(calendarBlock);
        layout->addWidget(eventBlock);
        setMinimumSize(QSize(900,500));
        setLayout(layout);
       // calendarLayout->setRowMinimumHeight(0, calendar->sizeHint().height());
//        calendarLayout->setColumnMinimumWidth(0, calendar->sizeHint().width());
}

MainWindow::~MainWindow() {

}

void MainWindow::addCalendar() {
        calendarBlock = new QGroupBox(tr("Calendar"));
        calendar = new QCalendarWidget;
      //  calendar->setMinimumDate(QDate(1900, 1, 1));
      //  calendar->setMaximumDate(QDate(3000, 1, 1));
        calendar->setGridVisible(true);
        calendar->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
        calendar->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
     /**   QTableView *view = calendar->findChild<QTableView*>("qt_calendar_calendarview");
        if (view)
        {
            QPalette pal = view->palette();
            pal.setColor(QPalette::Button, Qt::black);
            pal.setColor(QPalette::AlternateBase, Qt::green);
            view->setPalette(pal);
        }**/

       // connect(calendar, &QCalendarWidget::currentPageChanged, this , &MainWindow::seeEvent );

        calendarLayout = new QGridLayout;
        calendarLayout->addWidget(calendar, 0, 0);
        calendarBlock->setLayout(calendarLayout);
}

void MainWindow::addEventBox() {
        eventBlock = new QGroupBox(tr("Eventi"));
        eventLayout= new QVBoxLayout;
        eventLayoutTop = new QHBoxLayout;
        eventLayoutBot= new QVBoxLayout;
        eventLayout->setAlignment(Qt::AlignTop);

        //eventLayoutTop
        currentDateEdit = new QDateEdit;
        currentDateEdit->setDisplayFormat("dd MM yyyy");
        currentDateEdit->setDate(calendar->selectedDate());
        currentDateEdit->setDateRange(calendar->minimumDate(),
                                      calendar->maximumDate());
        currentDateEdit->setFixedSize(QSize(100,20));


        currentDateLabel = new QLabel(tr("Current Date"));
        currentDateLabel->setBuddy(currentDateEdit);

        connect(currentDateEdit, &QDateEdit::dateChanged,
                calendar, &QCalendarWidget::setSelectedDate);
        connect(calendar, &QCalendarWidget::selectionChanged, this , &MainWindow::selectedDateChanged);

        eventLayoutTop->setAlignment(Qt::AlignCenter);
        eventLayoutTop->addWidget(currentDateLabel);
        eventLayoutTop->addWidget(currentDateEdit);

        //eventLayoutBot

        addEvent= new QPushButton(tr("Add Event"));
        connect(addEvent, &QPushButton::clicked, this, &MainWindow::addNewEvent);

        areaEventi = new QScrollArea();

        areaEventi->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
        eventLayoutBot->addWidget(areaEventi);
        eventLayoutBot->addWidget(addEvent);

        //aggiunta LayoutBot e Top a eventLayout

        eventLayout->addLayout(eventLayoutTop);
        eventLayout->addLayout(eventLayoutBot);



        eventBlock->setMaximumWidth(400);
        eventBlock->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Expanding);
        eventBlock->setLayout(eventLayout);


}




void MainWindow::selectedDateChanged() {
    currentDateEdit->setDate(calendar->selectedDate());
}

void MainWindow::addNewEvent() {
    QWidget * popup = new QWidget();
    popup->show();
}

void MainWindow::addMenu() {

}

void MainWindow::seeEvent(){

}
