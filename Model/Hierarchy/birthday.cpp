#include "birthday.h"

BirthDay::BirthDay(unsigned short annoNasc,const std::string& nome,
                   const std::string& descr,const std::string& luogo,
                   const Date& dataEvento,const std::vector<std::string>& vettoreTag)
    :Event(nome,descr,luogo,dataEvento,vettoreTag),
    AllDayEvent (),
    annoNascita(annoNasc) {}

BirthDay *BirthDay::clone() const{
    return new BirthDay(*this);
}

void BirthDay::serialize(QJsonObject &json) const{
    AllDayEvent::serialize(json);
    json.insert("ID",BirthDay::ID);
    json["ANNO_NASCITA"] = QString::number(annoNascita);
}

unsigned short BirthDay::getNascita() const {
    return annoNascita;
}

void BirthDay::setNascita(const unsigned short& anno) {annoNascita=anno;}
