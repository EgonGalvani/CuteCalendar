#ifndef REMINDER_H
#define REMINDER_H

#include "eventwithduration.h"
#include "alert.h"

class Reminder : public EventWithDuration, Alert {
    //DOVE METTERE GLI ENUM
private:
    enum urgency {
        LOW = 0,
        MEDIUM,
    };

    urgency urg;
public:
    Reminder(int x,Time start,Time end,Time alert,bool rep,std::string nome,
             std::string descr,std::string luogo,Date data,std::vector<std::string>* tag);

    urgency getUrgency()const ;

    //virtual
    void serialize(QJsonObject &json)const ;
    Reminder* clone()const ;


};

#endif // REMINDER_H
