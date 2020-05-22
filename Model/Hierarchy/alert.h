#ifndef ALERT_H
#define ALERT_H
#include "event.h"

class Alert :virtual public Event{
private:
    Time alertTime;
    bool repeat;
public:

    Alert(Time alertTime,bool repeat,std::string nome = "",std::string descr = ""
            ,std::string luogo = "", Date data = Date(),
                             std::vector<std::string>* tags = nullptr);

    void setAlertTime(const Time alertTime);
    void setRepeat(const bool repeat);

    Time getAlertTime() const;
    bool doesRepeat() const;

    void serialize(QJsonObject &json) const;

};

#endif // ALERT_H
