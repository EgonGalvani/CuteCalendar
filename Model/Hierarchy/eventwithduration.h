#ifndef EVENTWITHDURATION_H
#define EVENTWITHDURATION_H

#include "event.h"

class EventWithDuration : virtual public Event {
    Time startTime;
    Time endTime;

public:
    //virtual
    Time getDuration()const ;
    bool isCompleted()const ;

    EventWithDuration(const Time& start,const Time& end,
                      const std::string& nome = "",const std::string& descr = "",
                      const std::string& luogo = "",const Date& data = Date(),
                      const std::vector<std::string>& tags = std::vector<std::string>());

    //GETTER SETTER
    Time getStartTime()const ;
    Time getEndTime()const ;
    void setStartTime(const Time start);
    void setEndTime(const Time end);

    void serialize(QJsonObject &json) const;
};

#endif // EVENTWITHDURATION_H
