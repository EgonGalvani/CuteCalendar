#ifndef ALERT_H
#define ALERT_H
#include "event.h"

class Alert :virtual public Event{
private:
    Time alertTime;
    bool repeat;
public:
    Alert(Time x,bool y,std::string nome = "",std::string descr = ""
            ,std::string luogo = "", Date data = Date(),
                             std::vector<std::string>* tags = nullptr);

    void setAlertTime(const Time x);
    void setRepeat(const bool x);

    Time getAlertTime() const;
    bool doesRepeat() const;

    void serialize(QJsonObject &json) const;

};

#endif // ALERT_H
