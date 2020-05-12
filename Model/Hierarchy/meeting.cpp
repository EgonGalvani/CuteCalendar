#include "meeting.h"

std::vector<std::string> Meeting::getPartecipants() {
    return partEmails;
}


Meeting::Meeting(std::vector<std::string> part, Time start,
        Time end, Time alert,bool repeat, std::string nome,std::string descr,
        std::string luogo,Date data,std::vector<std::string>* vettoreTag)

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

    json = Event::toJson();
    json.insert("ID","3");
    QJsonArray partArray;
    foreach (const std::string part, partEmails) {
        partArray.append(QString::fromStdString(part));
    }
    json["PARTECIPANTS"] = partArray;

}
//MANCA UN METODO PER MODIFICARE I VETTORI?

