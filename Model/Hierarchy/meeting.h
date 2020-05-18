#ifndef MEETING_H
#define MEETING_H

#include "eventwithduration.h"
#include "alert.h"

class Meeting : public EventWithDuration,public Alert {
private:
    std::vector<std::string> partEmails;

public:

    static const int ID = 3;

    Meeting* clone()const ;

    Meeting(std::vector<std::string> part, Time start,
            Time end, Time alert,bool repeat, std::string nome,std::string descr,
            std::string luogo,Date data,std::vector<std::string>* vettoreTag);
    std::vector<std::string> getPartecipants();

    //virtual
    void serialize(QJsonObject &json)const ;
};

#endif // MEETING_H
