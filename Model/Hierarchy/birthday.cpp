#include "birthday.h"

BirthDay::BirthDay(Date x, std::string nome,std::string descr,std::string luogo,
                   Date data,std::vector<std::string>* vettoreTag)
    :Event(nome,descr,luogo,data,vettoreTag),
    AllDayEvent (),
    dataNascita(x)
{

}

BirthDay *BirthDay::clone() {

    return new BirthDay(*this);

}

void BirthDay::serialize() {

}
Time BirthDay::getDuration() {
    return AllDayEvent::getDuration();
}
bool BirthDay::isCompleted() {
    return dataNascita<Date();
}

