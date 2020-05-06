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

    void setAlertTime(Time x);
    void setRepeat(bool x);

    Time getAlertTime();
    bool doesRepeat();

};

#endif // ALERT_H
