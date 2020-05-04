#include "meeting.h"

std::vector<std::string> Meeting::getPartecipants() {
    return partEmails;
}


Meeting::Meeting(std::vector<std::string> part, Time start,
        Time end, Time alert,bool repeat, std::string nome,std::string descr,
        std::string luogo,Date data,std::vector<std::string>* vettoreTag)

      : EventWithDuration (start,end,nome,descr,luogo,data,vettoreTag),
      Alert (alert,repeat, nome,descr,luogo,data,vettoreTag),
      partEmails(part)
{

}

//MANCA UN METODO PER MODIFICARE I VETTORI?

