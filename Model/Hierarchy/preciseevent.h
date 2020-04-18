#ifndef PRECISEEVENT_H
#define PRECISEEVENT_H

#include "uniqueevent.h"
#include "eventwithduration.h"

class PreciseEvent : public UniqueEvent,EventWithDuration {

public:
    virtual bool isCompleted();
};

#endif // PRECISEEVENT_H
