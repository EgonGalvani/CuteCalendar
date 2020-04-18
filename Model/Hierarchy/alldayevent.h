#ifndef ALLDAYEVENT_H
#define ALLDAYEVENT_H

#include "timemanager.h"
#include "event.h"

class AllDayEvent :public Event,TimeManager{
private:
    QTime* alertTime;
public:
    virtual QTime* getDuration() = 0;
    QTime* getAlertTime();
    void setAlertTime(QTime* time);

};

#endif // ALLDAYEVENT_H
