#include "birthday.h"

BirthDay::BirthDay(Date x, std::string nome,std::string descr,std::string luogo,
                   Date data,std::vector<std::string>* vettoreTag)
    :Event(nome,descr,luogo,data,vettoreTag),
    AllDayEvent (),
    dataNascita(x)
{

}

BirthDay *BirthDay::clone() const{

    return new BirthDay(*this);

}

void BirthDay::serialize() const{

}

