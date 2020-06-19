#include "eventwithduration.h"

EventWithDuration::EventWithDuration(const Time& start,const Time& end,
                                     const std::string& nome,const std::string& descr,
                                     const std::string& luogo,const Date& data,
                                     const std::vector<std::string>&tags)
    : Event(nome,descr,luogo,data,tags),
      _startTime(start),_endTime(end){}


Time EventWithDuration::getDuration() const {
    return _endTime-_startTime;
}

bool EventWithDuration::isCompleted() const {
    //Controlla se la data è passata, altrimenti se non lo è controlla se
    //è il giorno corrente && controlla che la l'ora di fine sia < di quella attuale
   return Event::getDate()<Date() || (getDate() == Date() && _endTime<Time());
}

void EventWithDuration::serialize(QJsonObject &json) const{
    Event::serialize(json);
    json["START_TIME"] = QString::fromStdString(_startTime.toString());
    json["END_TIME"] = QString::fromStdString(_endTime.toString());

}

//GETTER SETTER
Time EventWithDuration::getStartTime() const {return  _startTime;}
Time EventWithDuration::getEndTime() const {return _endTime;}
void EventWithDuration::setStartTime(const Time start) {_startTime=start;}
void EventWithDuration::setEndTime(const Time end) {_endTime=end;}


