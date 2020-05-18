#ifndef FACTORY_H
#define FACTORY_H

#include "birthday.h"
#include "meeting.h"
#include "reminder.h"
#include "workout.h"

class Factory {



public:
    static Event* parse(QJsonObject &json) {

        //Inizializzazione variabili

        Date date;
        QJsonArray tmp;
        std::vector<std::string>* tags = new std::vector<std::string>;
        int urg;
        int act;
        std::vector<std::string> vectPart = std::vector<std::string>();
        Time start;
        Time end;
        Date birth;
        Time alert;
        bool rep = false;
        std::istringstream temp;

        QJsonDocument doc(json);
        QString strJson(doc.toJson(QJsonDocument::Compact));
        std::cout<<strJson.toStdString()<<std::endl;

        //USO stoi e non .toInt perchè toInt ritorna sempre valore di default
        int x = std::stoi(json["ID"].toString().toStdString());
        //MANCA TODOLIST
        //Ricavo dei campi dati di evento
        std::string nome = json["NAME"].toString().toStdString();
        //conversione stringa -> data
        temp= std::istringstream(json["DATA"].toString().toStdString());
        std::cout<<std::endl<<"--DATA" <<json["DATA"].toString().toStdString()<<std::endl;
        temp>>date;
        std::string descr = json["DESCRIPTION"].toString().toStdString();
        std::string place = json["PLACE"].toString().toStdString();
        //conversione jsonarray -> array stringhe
        tmp = json["TAGS"].toArray();
        for (QJsonArray::const_iterator it = tmp.begin();it!=tmp.end();++it) {
            tags->push_back(it->toString().toStdString());
        }
        if (x!=BirthDay::ID) {
            temp= std::istringstream(json["START_TIME"].toString().toStdString());
            temp>>start;
            temp= std::istringstream(json["END_TIME"].toString().toStdString());
            temp>>end;
            //FAR DIVENTARE UNA CONST IL 2
            //CAMPO STATICO IN OGNI GERARCHIA CHE INDICA L'ID
            if (x!=Workout::ID) {
                rep = json["REPEAT"].toBool();
                //conversione stringa -> time
                temp= std::istringstream(json["ALERT_TIME"].toString().toStdString());
                temp>>alert;
            }
        }
        switch (x) {
        case Reminder::ID:
            //REMINDER = 1
            urg = json["URGENCY"].toInt();
            return new Reminder(urg,start,end,alert,rep,nome,descr,place,date,tags);
        case Workout::ID:
            //WORKOUT int x,Time start,Time end
            act = json["ACTIVITY"].toInt();
            return new Workout(act,start,end,nome,descr,place,date,tags);
        case Meeting::ID:
            //MEETING
            tmp = json["PARTECIPANTS"].toArray();
            for (QJsonArray::const_iterator it = tmp.begin();it!=tmp.end();++it) {
                vectPart.push_back(it->toString().toStdString());
            }
            return new Meeting(vectPart,start,end,alert,rep,nome,descr,place,date,tags);
        case BirthDay::ID:
            //BIRTHDAY
            temp= std::istringstream(json["DATA_NASCITA"].toString().toStdString());
            temp>>birth;
            return new BirthDay(birth,nome,descr,place,date,tags);
        }
        return nullptr;
    }
};

#endif // FACTORY_H
