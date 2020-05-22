#include "birthday.h"

BirthDay::BirthDay(const Date& dataNasc,const std::string& nome,
                   const std::string& descr,const std::string& luogo,
                   const Date& dataEvento,const std::vector<std::string>& vettoreTag)
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
