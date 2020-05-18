#ifndef COMPLEANNO_H
#define COMPLEANNO_H

#include "alldayevent.h"

class BirthDay : public AllDayEvent {

private:
    Date dataNascita;

public:

    static const int ID = 4;

    Date getNascita() const;

    BirthDay(Date dataNasc,std::string nome,std::string descr,std::string luogo,
             Date dataEvento,std::vector<std::string>* vettoreTag);

    BirthDay* clone() const;

    void serialize(QJsonObject &json) const;
};


#endif // COMPLEANNO_H
