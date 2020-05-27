#include "reminder.h"

Reminder::urgency Reminder::getUrgency() const {return urg;}

Reminder::Reminder(const int& urgenza,const Time& start,const Time& end,
                   const Time& alert, bool rep,const std::string& nome,
                   const std::string& descr,const std::string& luogo,
                   const Date& data,const std::vector<std::string>& tags)
    : Event(nome,descr,luogo,data,tags),
      EventWithDuration (start,end),
      Alert(alert,rep),
      urg(static_cast<urgency>(urgenza))
{ }

Reminder* Reminder::clone() const {
    return new Reminder(*this);
}

void Reminder::serialize(QJsonObject &json) const {
    EventWithDuration::serialize(json);
    Alert::serialize(json);
    json.insert("ID",Reminder::ID);
    json["URGENCY"] = urg;
}
