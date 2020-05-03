#ifndef MYCALENDAR_H
#define MYCALENDAR_H

#include <QWidget>
#include <QCalendarWidget>
#include <QPainter>
#include <QPen>
#include <QColor>
class MyCalendar : public QCalendarWidget
{
public:
    MyCalendar(QWidget* parent=0);
    ~MyCalendar();

protected:
    void paintCell(QPainter *painter, const QRect &rect, const QDate &date) const override;

};

#endif // MYCALENDAR_H
