#include "mainwindow.h"
#include "mycalendar.h"
#include "newEvent.h"


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



MainWindow::~MainWindow()
{


}

void MainWindow::addCalendar()
{
        calendarBlock = new QGroupBox(tr("Calendar"));
        calendar = new MyCalendar();
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

void MainWindow::addEventBox()
{
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


        eventLayoutBot->addWidget(areaEventi);
        eventLayoutBot->addWidget(addEvent);


        auto * container = new QWidget();
        //ScrollAreaFilling
        QVBoxLayout * layoutArea = new QVBoxLayout(container);

        auto * button1 = new QPushButton( "1", container);
        auto * button2 = new QPushButton( "2", container);
        auto * button3 = new QPushButton( "3", container);
        layoutArea->addWidget( button1 );
        layoutArea->addWidget( button2 );
        layoutArea->addWidget( button3 );
        areaEventi->setWidget( container );

        areaEventi->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);



         //aggiunta LayoutBot e Top a eventLayout

        eventLayout->addLayout(eventLayoutTop);
        eventLayout->addLayout(eventLayoutBot);



        eventBlock->setMaximumWidth(400);
        eventBlock->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Expanding);
        eventBlock->setLayout(eventLayout);


}




void MainWindow::selectedDateChanged()
{
    currentDateEdit->setDate(calendar->selectedDate());
 //   QPainter *painter = new QPainter;
   // calendar->paintCell(painter,rect(),calendar->selectedDate());
}

void MainWindow::addNewEvent()
{

    NewEvent * popup = new NewEvent();
    popup->show();


}

void MainWindow::addMenu()
{

}


void MainWindow::seeEvent(){

}







