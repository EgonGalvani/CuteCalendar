#ifndef ALLDAYEVENT_H
#define ALLDAYEVENT_H


#include "event.h"

class AllDayEvent :virtual public Event{
private:
public:
    Time getDuration();
    bool isCompleted() = 0;

};

#endif // ALLDAYEVENT_H
