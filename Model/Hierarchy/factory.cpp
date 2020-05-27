#include "factory.h"


void Factory::firstParse() {

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
        tags.push_back(it->toString().toStdString());
    }

}

void Factory::secondParse() {

    if (id!=BirthDay::ID && id!=ToDoList::ID) {
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



Factory::Factory(QJsonObject &js) : json(js) {
    tags = std::vector<std::string>();
    vectPart = std::vector<std::string>();

}


Event* Factory::parse() {

    id = json["ID"].toInt();

    firstParse();
    secondParse();

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
        birth = (json["ANNO_NASCITA"].toInt());
        return new BirthDay(birth,nome,descr,place,date,tags);
    case ToDoList::ID:
        ToDoList* temp = new ToDoList(nome,descr,place,date,tags);
        tmp = json["TODOLIST"].toArray();
        for (QJsonArray::const_iterator it = tmp.begin();it!=tmp.end();++it) {
            temp->addItem((*it)["item_description"].toString().toStdString(),(*it)["item_isdone"].toBool());
        }
        return temp;
    }
    return nullptr;
}

