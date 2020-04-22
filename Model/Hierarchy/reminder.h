#ifndef REMINDER_H
#define REMINDER_H

#include "preciseevent.h"

class Reminder : public PreciseEvent {
    //DOVE METTERE GLI ENUM
private:
    enum Urgency {

    };

    Urgency urg;
public:
    virtual void serialize();
    Urgency getUrgency();

};

#endif // REMINDER_H
