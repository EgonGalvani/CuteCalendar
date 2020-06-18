#include "factory.h"




void Factory::firstCheck() const {
    //Controlla che i primi tre campi in comune a tutti gli eventi siano validi
    //Se non lo sono lancia una eccezione
    if (nome.empty() || descr.empty() || place.empty())
        throw std::runtime_error("Salvataggio corrotto : campi fondamentali vuoti o di tipo errato");
}

void Factory::firstParse() {
    //Ricavo dei campi dati di evento
    nome = json["NAME"].toString().toStdString();
    //conversione stringa -> data
    temp= std::istringstream(json["DATA"].toString().toStdString());
    temp>>date;
    descr = json["DESCRIPTION"].toString().toStdString();
    place = json["PLACE"].toString().toStdString();
    //conversione jsonarray -> array stringhe
    tmp = json["TAGS"].toArray();
    for (QJsonArray::const_iterator it = tmp.begin();it!=tmp.end();++it) {
        std::string tag = it->toString().toStdString();
        //Check se tag sono empty(formato sbagliato es)
        if (!tag.empty())
            tags.push_back(it->toString().toStdString());
    }
}

void Factory::secondParse() {
    //campi in comune a tutti gli eventi tranne birthday e todolist
    if (id!=BirthDay::ID && id!=ToDoList::ID) {
        //il Check di validità del formato è già dentro time e date
        temp= std::istringstream(json["START_TIME"].toString().toStdString());
        temp>>start;
        temp= std::istringstream(json["END_TIME"].toString().toStdString());
        temp>>end;
        //Campi in comune a tutti gli eventi tranne che workout e quelli precedenti
        if (id!=Workout::ID) {
            rep = json["REPEAT"].toBool();
            //automatico false in caso di formato errato
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

bool Factory::isEmail(const std::string& email) const{
   // define a regular expression
   const std::regex pattern
      ("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");

   // try to match the string with the regular expression
   return std::regex_match(email, pattern);
}

Event* Factory::parse() {

    //ricava l'id,campo fondamentale per il parsing
    id = json["ID"].toInt();

    //l'id 0 è riservato e se è maggiore di nEventi significa che è un campo corrotto
    //o modificato
    if (id == 0 || id>nEventi) throw std::runtime_error("Salvataggio corrotto : ID INVALIDO");
    //parse campi in comune a tutti
    firstParse();
    //controllo validità
    firstCheck();
    //parse campi in comune alla maggior parte degli eventi
    secondParse();


    //Parse dei campi che sono unici per ogni evento(quindi mai in comune con altri)
    switch (id) {
    case Reminder::ID:
        urg = json["URGENCY"].toInt();
        if (urg==0) {
            throw std::runtime_error("Salvataggio corrotto : campo priotità vuoto o di tipo errato");
        }
        return new Reminder(urg,start,end,alert,rep,nome,descr,place,date,tags);
    case Workout::ID:
        act = json["ACTIVITY"].toInt();
        if (act==0) {
            throw std::runtime_error("Salvataggio corrotto : campo attività vuoto o di tipo errato");
        }
        return new Workout(act,start,end,nome,descr,place,date,tags);
    case Meeting::ID:
        tmp = json["PARTECIPANTS"].toArray();
        //estrae i valori dal qjsonarray e inserisce dentro il vettore dopo
        //opportune conversioni
        for (QJsonArray::const_iterator it = tmp.begin();it!=tmp.end();++it) {
            std::string mail = it->toString().toStdString();
            //Check se email sono empty e se il formato è corretto
            if (!mail.empty() && isEmail(mail))
                //inserisce la stringa nel vettore
                vectPart.push_back(mail);
        }
        return new Meeting(vectPart,start,end,alert,rep,nome,descr,place,date,tags);
    case BirthDay::ID:
        birth = (json["ANNO_NASCITA"].toInt());
        if (birth==0) {
            throw std::runtime_error("Salvataggio corrotto : campo anno nascita vuoto o di tipo errato");
        }
        return new BirthDay(birth,nome,descr,place,date,tags);
    case ToDoList::ID:
        ToDoList* temp = new ToDoList(nome,descr,place,date,tags);
        tmp = json["TODOLIST"].toArray();
        //itera il qjsonarray ed estrae i vari oggetti che compongono la todolist
        for (QJsonArray::const_iterator it = tmp.begin();it!=tmp.end();++it) {
            QJsonObject itemObject = (*it).toObject();
            //estrae la descrizione dell'oggetto
            std::string item_desc = itemObject["item_description"].toString().toStdString();
            //controlla che la descrizione sia valida
            if (!item_desc.empty())
                //se la descrizione è valida inserisce un nuovo item nella todolist
                temp->addItem(item_desc,itemObject["item_isdone"].toBool());
        }
        return temp;
    }

    return nullptr;
}

