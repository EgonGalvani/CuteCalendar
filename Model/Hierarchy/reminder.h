#ifndef REMINDER_H
#define REMINDER_H

#include "preciseevent.h"

class Reminder : public PreciseEvent {

    enum Urgency {

    };

    virtual void serialize();
    Urgency getUrgency();

};

#endif // REMINDER_H
