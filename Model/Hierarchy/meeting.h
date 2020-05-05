#ifndef MEETING_H
#define MEETING_H

#include "eventwithduration.h"
#include "alert.h"

class Meeting : public EventWithDuration,Alert {
private:
    std::vector<std::string> partEmails;

public:

    Meeting* clone();

    Meeting(std::vector<std::string> part, Time start,
            Time end, Time alert,bool repeat, std::string nome,std::string descr,
            std::string luogo,Date data,std::vector<std::string>* vettoreTag);
    std::vector<std::string> getPartecipants();

    //virtual
    void serialize();
    Time getDuration();
    bool isCompleted();

};

#endif // MEETING_H
