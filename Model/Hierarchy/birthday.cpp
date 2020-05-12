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

void BirthDay::serialize(QJsonObject &json) const{
    json = Event::toJson();
    json.insert("ID","4");
    json["Data_Nascita"] = QString::fromStdString(dataNascita.toString());

}

