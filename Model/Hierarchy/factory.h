#ifndef FACTORY_H
#define FACTORY_H

#include "birthday.h"
#include "meeting.h"
#include "reminder.h"
#include "workout.h"

class Factory {

private:


    static QJsonObject json;

    static Date date;
    static std::string nome;
    static std::string descr;
    static std::string place;
    static QJsonArray tmp;
    static std::vector<std::string>* tags;
    static int urg;
    static int act;
    static std::vector<std::string> vectPart;
    static Time start;
    static Time end;
    static Date birth;
    static Time alert;
    static bool rep;
    static std::istringstream temp;

    static void initializeVariables() {

        date = Date();
        tags =  new std::vector<std::string>;
        vectPart = std::vector<std::string>();
        start = Time();
        end = Time();
        birth = Date();
        alert= Time();
        rep = false;
    }

    static void firstParse() {

        //MANCA TODOLIST
        //Ricavo dei campi dati di evento
        nome = json["NAME"].toString().toStdString();
        //conversione stringa -> data
        temp= std::istringstream(json["DATA"].toString().toStdString());
        std::cout<<std::endl<<"--DATA" <<json["DATA"].toString().toStdString()<<std::endl;
        temp>>date;
        descr = json["DESCRIPTION"].toString().toStdString();
        place = json["PLACE"].toString().toStdString();
        //conversione jsonarray -> array stringhe
        tmp = json["TAGS"].toArray();
        for (QJsonArray::const_iterator it = tmp.begin();it!=tmp.end();++it) {
            tags->push_back(it->toString().toStdString());
        }

    }

    static void secondParse(int id) {

        if (id!=BirthDay::ID) {
            temp= std::istringstream(json["START_TIME"].toString().toStdString());
            temp>>start;
            temp= std::istringstream(json["END_TIME"].toString().toStdString());
            temp>>end;
            if (id!=Workout::ID) {
                rep = json["REPEAT"].toBool();
                //conversione stringa -> time
                temp= std::istringstream(json["ALERT_TIME"].toString().toStdString());
                temp>>alert;
            }
        }

    }

public:


    static Event* parse(QJsonObject &js) {

        json = js;

        initializeVariables();

        //USO stoi e non .toInt perchè toInt ritorna sempre valore di default
        int id = std::stoi(json["ID"].toString().toStdString());

        firstParse();
        secondParse(id);

        switch (id) {
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
