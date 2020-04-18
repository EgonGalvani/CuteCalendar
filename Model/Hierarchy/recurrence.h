#ifndef RECURRENCE_H
#define RECURRENCE_H

#include <QDate>
#include "recurrencerule.h"
#include "datemanager.h"
#include "event.h"

class Recurrence : public DateManager,Event{
private:
    QDate* startDate;
    QDate* endDate;
    RecurrenceRule* period;

    //Virtual methods
public:
    virtual bool isCompleted();
    virtual bool isToday(QDate* day);
    virtual bool isInInterval(QDate* beg,QDate* end);

    //Getter

    //Intende ha una fine o è finito?
    bool hasEnd();
    QDate* getNextEvent();


};

#endif // RECURRENCE_H
