#ifndef EVENTWITHDURATION_H
#define EVENTWITHDURATION_H


#include "event.h"

class EventWithDuration :virtual public Event {
    Time startTime;
    Time endTime;
public:
    //virtual
    Time getDuration();
    bool isCompleted();

    EventWithDuration(Time start,Time end,std::string nome = "",std::string descr = ""
            ,std::string luogo = "", Date data = Date(),
                             std::vector<std::string>* tags = nullptr);

    //GETTER SETTER
    Time getStartTime();
    Time getEndTime();
    void setStartTime(Time start);
    void setEndTime(Time end);



};

#endif // EVENTWITHDURATION_H
