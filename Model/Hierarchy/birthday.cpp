#include "birthday.h"

BirthDay::BirthDay(Date dataNasc, std::string nome,std::string descr,std::string luogo,
                   Date dataEvento,std::vector<std::string>* vettoreTag)
    :Event(nome,descr,luogo,dataEvento,vettoreTag),
    AllDayEvent (),
    dataNascita(dataNasc) {}

BirthDay *BirthDay::clone() const{
    return new BirthDay(*this);
}

void BirthDay::serialize(QJsonObject &json) const{
    AllDayEvent::serialize(json);
    json.insert("ID","4");
    json["DATA_NASCITA"] = QString::fromStdString(dataNascita.toString());
}

Date BirthDay::getNascita() const {
    return dataNascita;
}
