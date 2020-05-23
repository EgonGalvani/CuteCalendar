#ifndef MEETING_H
#define MEETING_H

#include "eventwithduration.h"
#include "alert.h"

class Meeting : public EventWithDuration, public Alert {
private:
    std::vector<std::string> partEmails;

public:

    static const int ID = 3;

    Meeting* clone()const ;

    Meeting(const std::vector<std::string>& part,const Time& start,
            const Time& end,const Time& alert,const bool& repeat,
            const std::string& nome,const std::string& descr,
            const std::string& luogo,const Date& data,
            const std::vector<std::string>& vettoreTag);
    std::vector<std::string> getPartecipants() const;

    //virtual
    void serialize(QJsonObject &json)const ;
};

#endif // MEETING_H
