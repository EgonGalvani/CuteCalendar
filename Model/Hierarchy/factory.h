#ifndef FACTORY_H
#define FACTORY_H

#include "birthday.h"
#include "meeting.h"
#include "reminder.h"
#include "workout.h"

class Factory {

private:


    QJsonObject json;

    Date date;
    std::string nome;
    std::string descr;
    std::string place;
    QJsonArray tmp;
    std::vector<std::string>tags;
    int urg;
    int act;
    std::vector<std::string> vectPart;
    Time start;
    Time end;
    Date birth;
    Time alert;
    bool rep;
    std::istringstream temp;
    int id;

    void firstParse();

    void secondParse();

public:

    Factory(QJsonObject &js);

    Event* parse();
};

#endif // FACTORY_H
