#include "eventwithduration.h"

EventWithDuration::EventWithDuration(Time start, Time end,
                                     std::string nome,std::string descr,std::string luogo,
                                     Date data,std::vector<std::string> *tags)
    : Event(nome,descr,luogo,data,tags),
      startTime(start),endTime(end){}

Time EventWithDuration::getDuration() {
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

bool EventWithDuration::isCompleted() {
    return endTime<*(new Time());
}

//GETTER SETTER
Time EventWithDuration::getStartTime() {return  startTime;}
Time EventWithDuration::getEndTime() {return endTime;}
void EventWithDuration::setStartTime(Time start) {startTime=start;}
void EventWithDuration::setEndTime(Time end) {endTime=end;}
