#include "alldayevent.h"

//
AllDayEvent::AllDayEvent(std::string nome,std::string descr
        ,std::string luogo, Date data,
                         std::vector<std::string>* tags)
    :Event(nome,descr,luogo,data,tags) {}

Time AllDayEvent::getDuration() {
    return Time(23,59,59);
}

