#ifndef RECURRENCE_H
#define RECURRENCE_H

#include <QDate>
#include "recurrencerule.h"
#include "datemanager.h"

class Recurrence : public DateManager{
private:
    QDate* startDate;
    QDate* endDate;
    RecurrenceRule* period;

    //Virtual methods
public:
    virtual bool isCompleted();
    virtual bool isToday(QDate* day);


};

#endif // RECURRENCE_H
