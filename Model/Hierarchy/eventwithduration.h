#ifndef EVENTWITHDURATION_H
#define EVENTWITHDURATION_H

#include "timemanager.h"
#include "event.h"

class EventWithDuration : public Event,TimeManager {
    QTime* startTime;
    QTime* endTime;

    virtual QTime* getDuration();

    //GETTER SETTER
    QTime* getStartTime();
    QTime* getEndTime();
    void setStartTime(QTime* start);
    void setEndTime(QTime* end);
};

#endif // EVENTWITHDURATION_H
