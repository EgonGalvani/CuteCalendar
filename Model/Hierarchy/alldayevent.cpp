#include "alldayevent.h"



AllDayEvent::AllDayEvent(std::string nome,std::string descr,std::string luogo,
                         Date data,std::vector<std::string>* vettoreTag)
    : Event(nome,descr,luogo,data,vettoreTag)
{

}
