#ifndef UNIQUEEVENT_H
#define UNIQUEEVENT_H

#include "datemanager.h"
#include "event.h"

class UniqueEvent : public Event,DateManager {

    QDate* date;

    virtual bool isInInterval(QDate* start,QDate* end);

};

#endif // UNIQUEEVENT_H
