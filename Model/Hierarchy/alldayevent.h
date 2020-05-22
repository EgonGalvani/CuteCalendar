#ifndef ALLDAYEVENT_H
#define ALLDAYEVENT_H


#include "event.h"

class AllDayEvent :virtual public Event{
private:
public:
    AllDayEvent(const std::string& nome = "",const std::string& descr = ""
            ,const std::string& luogo = "", const Date& data = Date(),
                             const std::vector<std::string>& tags = std::vector<std::string>());
    Time getDuration() const;

    void serialize(QJsonObject &json) const;

};

#endif // ALLDAYEVENT_H
