#include "workout.h"

Workout::activity Workout::getActivity() const  {return act;}
void Workout::setActivity(int x) {act = static_cast<activity>(x);}

void Workout::serialize(QJsonObject &json) const {
    EventWithDuration::serialize(json);
    json.insert("ID","2");
    json["ACTIVITY"] = act;
}

Workout::Workout(const int& attivita,const Time& start,const Time& end,
                 const std::string& nome,const std::string& descr,
                 const std::string& luogo,const Date& data,
                 const std::vector<std::string>& tags)
      : Event(nome,descr,luogo,data,tags),
        EventWithDuration (start,end)


{
    act = static_cast<activity>(attivita);
}

Workout* Workout::clone() const {
    return new Workout(*this);
}
