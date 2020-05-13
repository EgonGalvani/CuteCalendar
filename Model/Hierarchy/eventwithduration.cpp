#include "eventwithduration.h"

EventWithDuration::EventWithDuration(Time start, Time end,
                                     std::string nome,std::string descr,std::string luogo,
                                     Date data,std::vector<std::string> *tags)
    : Event(nome,descr,luogo,data,tags),
      startTime(start),endTime(end){}

Time EventWithDuration::getDuration() const {
    //POTREBBE ESSERCI UN METODO PIÙ EFFICACE,
    //Difference converted in seconds, e poi ricostruisco ora,minuti,secondi

    unsigned short x = (endTime - startTime).second();
    unsigned short hour = x / 3600;
    x %= 3600;
    unsigned short minutes = x / 60 ;
    x %= 60;
    unsigned short seconds = x;
    return Time(hour,minutes,seconds);
}

bool EventWithDuration::isCompleted() const {
    return Event::isCompleted() && endTime<Time();
}

void EventWithDuration::serialize(QJsonObject &json) const{

    Event::serialize(json);
    json["START_TIME"] = QString::fromStdString(startTime.toString());
    json["END_TIME"] = QString::fromStdString(endTime.toString());

}

//GETTER SETTER
Time EventWithDuration::getStartTime() const {return  startTime;}
Time EventWithDuration::getEndTime() const {return endTime;}
void EventWithDuration::setStartTime(const Time start) {startTime=start;}
void EventWithDuration::setEndTime(const Time end) {endTime=end;}


