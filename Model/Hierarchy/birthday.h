#ifndef COMPLEANNO_H
#define COMPLEANNO_H
#include "recurrence.h"
#include "alldayevent.h"

class BirthDay : public Recurrence,AllDayEvent {

private:

    QDate* dataNascita;
public:

    virtual void serialize();

};

#endif // COMPLEANNO_H
