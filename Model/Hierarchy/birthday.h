#ifndef COMPLEANNO_H
#define COMPLEANNO_H
#include "recurrence.h"
#include "alldayevent.h"

class BirthDay : public Recurrence,AllDayEvent {

private:

    QDate* dataNascita;
public:
    //PERCHÈ BirthDay eredita getDuration?...
    virtual QTime* getDuration();
    virtual void serialize();

};

#endif // COMPLEANNO_H
