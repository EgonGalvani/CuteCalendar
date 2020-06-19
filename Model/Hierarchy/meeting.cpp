#include "meeting.h"

std::vector<std::string> Meeting::getPartecipants() const{
    return partEmails;
}

void Meeting::addPartecipant(const std::string& part) {
    partEmails.push_back(part);
}

std::vector<std::string> Meeting::deletePartecipant(const std::string& part) {
    std::vector<std::string>::iterator it = partEmails.begin();
    //finchè il vettore non è stato completamente iterato
    while (it!=partEmails.end()) {
        //controlla se la stringa nella cella puntata è la stringa da eliminare
        if ((*it)==part) {
            it = partEmails.erase(it);
        }else {
            //se non lo è passa alla cella successiva
            ++it;
        }
    }
    //restituisce il nuovo vettore
    return partEmails;
}

bool Meeting::hasPartecipant(const std::string& part) const {
    bool found = false;
    //itera il vettore cercando la stringa desiderata,se la trova esce dal ciclo
    for (std::vector<std::string>::const_iterator it = partEmails.begin();
         !found && it!=partEmails.end();++it) {
        found = *it==part;
    }
    return found;
}

bool Meeting::atLeastOnePartecipant() const {
    return !partEmails.empty();
}

Meeting::Meeting(const std::vector<std::string>& part, const Time& start,
                 const Time& end,const Time& alert, bool repeat,
                 const std::string& nome, const std::string& descr,
                 const std::string& luogo, const Date& data,
                 const std::vector<std::string>& vettoreTag)
      : Event(nome,descr,luogo,data,vettoreTag),
      EventWithDuration (start,end),
      Alert (alert,repeat),
      partEmails(part)
{}

Meeting* Meeting::clone() const {
    return new Meeting(*this);
}

void Meeting::serialize(QJsonObject &json)const {
    EventWithDuration::serialize(json);
    Alert::serialize(json);
    json.insert("ID",Meeting::ID);
    QJsonArray partArray;
    foreach (const std::string part, partEmails) {
        partArray.append(QString::fromStdString(part));
    }

    json["PARTECIPANTS"] = partArray;
}
