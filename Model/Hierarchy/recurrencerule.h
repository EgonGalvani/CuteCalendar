#ifndef RECURRENCERULE_H
#define RECURRENCERULE_H
#include <QDate>
#include <vector>

class RecurrenceRule {
private:
    //Short?
    unsigned short period;

public:
    //Virtual methods
    virtual std::vector<QDate*>* getEvents(QDate* eventBeg,QDate* eventEnd,
                                           QDate* intervalStart,QDate* intervalEnd) = 0;

    virtual QDate* getNextEvent(QDate* from) = 0;

    //Getter
    unsigned int getPeriod();

    //Destructor

    virtual ~RecurrenceRule();

};

#endif // RECURRENCERULE_H
