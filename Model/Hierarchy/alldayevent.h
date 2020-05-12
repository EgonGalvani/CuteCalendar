#ifndef ALLDAYEVENT_H
#define ALLDAYEVENT_H


#include "event.h"

class AllDayEvent :virtual public Event{
private:
public:
    AllDayEvent(std::string nome = "",std::string descr = ""
            ,std::string luogo = "", Date data = Date(),
                             std::vector<std::string>* tags = nullptr);
    Time getDuration() const;

};

#endif // ALLDAYEVENT_H
