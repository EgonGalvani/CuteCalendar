#include "reminder.h"

Reminder::urgency Reminder::getUrgency() {return urg;}

Reminder::Reminder(int x,Time start,Time end,Time alert,bool rep,std::string nome,
                   std::string descr,std::string luogo,Date data,std::vector<std::string>* tag)
    : Event(nome,descr,luogo,data,tag),
      EventWithDuration (start,end),
      Alert(alert,rep),
      urg(static_cast<urgency>(x))
{

}

Reminder* Reminder::clone() {
    return new Reminder(*this);
}

void Reminder::serialize() {

}
Time Reminder::getDuration() {
    return EventWithDuration::getDuration();
}
bool Reminder::isCompleted() {
    return EventWithDuration::isCompleted();
}


