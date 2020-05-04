#ifndef ALLDAYEVENT_H
#define ALLDAYEVENT_H


#include "event.h"

class AllDayEvent :virtual public Event{
private:
public:
    virtual Time getDuration() = 0;
    virtual bool isCompleted() = 0;

    AllDayEvent(std::string nome,std::string descr,std::string luogo,
                Date data,std::vector<std::string>* vettoreTag);

};

#endif // ALLDAYEVENT_H
