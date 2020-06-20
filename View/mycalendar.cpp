#include "mycalendar.h"


MyCalendar::MyCalendar(const Model* m,QWidget *parent)
    : QCalendarWidget(parent) , model(m)
{}


//Coloro le celle del calendario che contengono un Evento o sono Selezionate
void MyCalendar::paintCell(QPainter *painter, const QRect &rect, const QDate &date) const {

    QColor color = (selectedDate() == date) ? QColor(159,249,246)
            : (model->hasEvent(date)) ? Qt::yellow
            : Qt::white;

    painter->save();
    painter->fillRect(rect, color);
    painter->drawText(rect, Qt::AlignCenter,QString::number(date.day()));
    painter->restore();
}
