#include "mycalendar.h"


MyCalendar::MyCalendar(QWidget *parent)
    : QCalendarWidget(parent)
{

}

MyCalendar::~MyCalendar()
{

}

void MyCalendar::paintCell(QPainter *painter, const QRect &rect, const QDate &date) const
{
    if (QCalendarWidget::selectedDate() == date) { // our conditions
                // When the conditions are matched, passed QDate is drawn as we like.
                painter->save();
                painter->fillRect(rect,Qt::yellow);
                painter->drawText(rect, Qt::AlignCenter,QString::number(date.day()));
                painter->restore();
            } else { // if our conditions are not matching, show the default way.
                QCalendarWidget::paintCell(painter, rect, date);
            }

}


