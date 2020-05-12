#include "workout.h"

Workout::activity Workout::getSport()const  {return act;}
void Workout::setSport(int x) {act = static_cast<activity>(x);}

void Workout::serialize(QJsonObject &json) const {
    EventWithDuration::serialize(json);
    json.insert("ID","2");
    json["ACTIVITY"] = act;
}

Workout::Workout(int x,Time start,Time end,std::string nome,std::string descr,
                 std::string luogo,Date data,std::vector<std::string>* tags)
      : Event(nome,descr,luogo,data,tags),
        EventWithDuration (start,end)


{
    act = static_cast<activity>(x);
}

Workout* Workout::clone() const {
    return new Workout(*this);
}

Workout::~Workout() {}
