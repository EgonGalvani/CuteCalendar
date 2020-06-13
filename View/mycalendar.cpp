#include "mycalendar.h"


MyCalendar::MyCalendar(const Model* m,QWidget *parent)
    : QCalendarWidget(parent) , model(m)
{}



void MyCalendar::paintCell(QPainter *painter, const QRect &rect, const QDate &date) const {
    if (selectedDate() == date || !model->hasEvent(date))
        QCalendarWidget::paintCell(painter, rect, date);
    else { // our conditions
        // When the conditions are matched, passed QDate is drawn as we like.
        painter->save();
        painter->fillRect(rect,Qt::yellow);
        painter->drawText(rect, Qt::AlignCenter,QString::number(date.day()));
        painter->restore();
    }
}
