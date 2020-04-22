#include "eventwithduration.h"

//QTime* startTime;
//QTime* endTime;

QTime* EventWithDuration::getDuration() {
    //POTREBBE ESSERCI UN METODO PIÙ EFFICACE,
    //Difference converted in seconds, e poi ricostruisco ora,minuti,secondi

    int x = startTime->secsTo(*endTime);
    int hour = x / 3600;
    x %= 3600;
    int minutes = x / 60 ;
    x %= 60;
    int seconds = x;
    return new QTime(hour,minutes,seconds);

}

//GETTER SETTER
QTime* EventWithDuration::getStartTime() {return  startTime;}
QTime* EventWithDuration::getEndTime() {return endTime;}
void EventWithDuration::setStartTime(QTime* start) {startTime=start;}
void EventWithDuration::setEndTime(QTime* end) {endTime=end;}
