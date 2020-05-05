#include "meeting.h"

std::vector<std::string> Meeting::getPartecipants() {
    return partEmails;
}


Meeting::Meeting(std::vector<std::string> part, Time start,
        Time end, Time alert,bool repeat, std::string nome,std::string descr,
        std::string luogo,Date data,std::vector<std::string>* vettoreTag)

      : Event(nome,descr,luogo,data,vettoreTag),
      EventWithDuration (start,end),
      Alert (alert,repeat),
      partEmails(part)
{

}

Meeting* Meeting::clone() {
    return new Meeting(*this);
}

void Meeting::serialize(){

}
//MANCA UN METODO PER MODIFICARE I VETTORI?

