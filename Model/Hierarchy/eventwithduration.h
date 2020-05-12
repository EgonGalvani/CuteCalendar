#ifndef EVENTWITHDURATION_H
#define EVENTWITHDURATION_H


#include "event.h"

class EventWithDuration :virtual public Event {
    Time startTime;
    Time endTime;
public:
    //virtual
    Time getDuration()const ;
    bool isCompleted()const ;

    EventWithDuration(Time start,Time end,std::string nome = "",std::string descr = ""
            ,std::string luogo = "", Date data = Date(),
                             std::vector<std::string>* tags = nullptr);

    //GETTER SETTER
    Time getStartTime()const ;
    Time getEndTime()const ;
    void setStartTime(const Time start);
    void setEndTime(const Time end);



};

#endif // EVENTWITHDURATION_H
