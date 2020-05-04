#include "birthday.h"

void BirthDay::serialize() {

}

BirthDay::BirthDay(Date x, std::string nome,std::string descr,std::string luogo,
                   Date data,std::vector<std::string>* vettoreTag)
    : AllDayEvent (nome,descr,luogo,data,vettoreTag),
    dataNascita(x)
{

}
