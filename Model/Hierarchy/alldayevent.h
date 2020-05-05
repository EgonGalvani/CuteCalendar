#ifndef ALLDAYEVENT_H
#define ALLDAYEVENT_H


#include "event.h"

class AllDayEvent :virtual public Event{
private:
public:
    AllDayEvent(std::string nome = nullptr,std::string descr = nullptr
            ,std::string luogo = nullptr, Date data = Date(),
                             std::vector<std::string>* tags = nullptr);
    Time getDuration();

};

#endif // ALLDAYEVENT_H
