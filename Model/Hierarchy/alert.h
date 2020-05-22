#ifndef ALERT_H
#define ALERT_H
#include "event.h"

class Alert :virtual public Event{
private:
    Time alertTime;
    bool repeat;
public:

    Alert(const Time& alertTime,const bool& repeat,const std::string& nome = "",
          const std::string& descr = "",const std::string& luogo = "",const Date& data = Date(),
                             const std::vector<std::string>& tags = std::vector<std::string>());

    void setAlertTime(const Time alertTime);
    void setRepeat(const bool repeat);

    Time getAlertTime() const;
    bool doesRepeat() const;

    void serialize(QJsonObject &json) const;

};

#endif // ALERT_H
