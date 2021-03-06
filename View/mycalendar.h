#ifndef MYCALENDAR_H
#define MYCALENDAR_H

#include <QWidget>
#include <QCalendarWidget>
#include <QPainter>
#include <QPen>
#include <QColor>
#include <Model/model.h>

class MyCalendar : public QCalendarWidget {
public:
    MyCalendar(const Model*,QWidget* parent=0);
    ~MyCalendar()=default;

protected:

    void paintCell(QPainter *painter, const QRect &rect, const QDate &date) const override;

private:
    // Puntatore al Model
    const Model* model;
};

#endif // MYCALENDAR_H
