#include "mycalendar.h"


MyCalendar::MyCalendar(const Model* m,QWidget *parent)
    : QCalendarWidget(parent) , model(m)
{}


//Coloro le celle del calendario che contengono un Evento o sono Selezionate
void MyCalendar::paintCell(QPainter *painter, const QRect &rect, const QDate &date) const {
    if (selectedDate() == date || !model->hasEvent(date))
        QCalendarWidget::paintCell(painter, rect, date);
    else {
        painter->save();
        painter->fillRect(rect,Qt::yellow);
        painter->drawText(rect, Qt::AlignCenter,QString::number(date.day()));
        painter->restore();
    }
}
