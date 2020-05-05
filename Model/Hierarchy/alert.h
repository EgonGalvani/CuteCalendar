#ifndef ALERT_H
#define ALERT_H
#include "event.h"

class Alert :virtual public Event{
private:
    Time alertTime;
    bool repeat;
public:
    Alert(Time x,bool y);

    void setAlertTime(Time x);
    void setRepeat(bool x);

    Time getDuration() = 0;
    bool isCompleted() = 0;

    Time getAlertTime();
    bool doesRepeat();

};

#endif // ALERT_H
