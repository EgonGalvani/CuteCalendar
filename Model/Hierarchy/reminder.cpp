#include "reminder.h"

Reminder::urgency Reminder::getUrgency() {return urg;}

Reminder::Reminder(int x,Time start,Time end,Time alert,bool rep,std::string nome,
                   std::string descr,std::string luogo,Date data,std::vector<std::string>* tag)
    : EventWithDuration (start,end,nome,descr,luogo,data,tag),
      Alert(alert,rep,nome,descr,luogo,data,tag),
      urg(static_cast<urgency>(x))
{

}

void Reminder::serialize() {

}
Time Reminder::getDuration() {
    return Time();
}
bool Reminder::isCompleted() {
    return false;
}


