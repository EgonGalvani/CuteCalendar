#include "meeting.h"

std::vector<std::string> Meeting::getPartecipants() {
    return partEmails;
}


Meeting::Meeting(const std::vector<std::string>& part,const Time& start,
                 const Time& end,const Time& alert,const bool& repeat,
                 const std::string& nome,const std::string& descr,const std::string& luogo,
                 const Date& data,const std::vector<std::string>& vettoreTag)

      : Event(nome,descr,luogo,data,vettoreTag),
      EventWithDuration (start,end),
      Alert (alert,repeat),
      partEmails(part)
{

}

Meeting* Meeting::clone() const {
    return new Meeting(*this);
}

void Meeting::serialize(QJsonObject &json)const {

    EventWithDuration::serialize(json);
    Alert::serialize(json);
    json.insert("ID","3");
    QJsonArray partArray;
    foreach (const std::string part, partEmails) {
        partArray.append(QString::fromStdString(part));
    }
    json["PARTECIPANTS"] = partArray;

}
//MANCA UN METODO PER MODIFICARE I VETTORI?

