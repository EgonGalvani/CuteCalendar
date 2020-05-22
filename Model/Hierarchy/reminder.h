#ifndef REMINDER_H
#define REMINDER_H

#include "eventwithduration.h"
#include "alert.h"

class Reminder : public EventWithDuration,public Alert {
private:
    enum urgency {
        LOW = 0,
        MEDIUM,
    };

    urgency urg;
public:

    static const int ID = 1;

    Reminder(const int& urgency,const Time& start,const Time& end,
             const Time& alert,const bool& rep,const std::string& nome,
             const std::string& descr,const std::string& luogo,
             const Date& data,const std::vector<std::string>& tag);

    urgency getUrgency()const ;

    //virtual
    void serialize(QJsonObject &json)const ;
    Reminder* clone()const ;


};

#endif // REMINDER_H
