#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QWidget(parent){
        addCalendar();
        addEventBox();
        QGridLayout *layout = new QGridLayout;
        layout->addWidget(calendarBlock, 0, 0);
        layout->addWidget(eventBlock,0,1);
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
        calendar->setMinimumDate(QDate(1900, 1, 1));
        calendar->setMaximumDate(QDate(3000, 1, 1));
        calendar->setGridVisible(true);
        calendar->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
        calendar->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
        calendarLayout = new QGridLayout;
        calendarLayout->addWidget(calendar, 0, 0);
        calendarBlock->setLayout(calendarLayout);

}

void MainWindow::addEventBox()
{
        eventBlock = new QGroupBox(tr("Eventi"));
        eventLayout= new QGridLayout;
        eventBlock->setLayout(eventLayout);


}










