#ifndef COMPLEANNO_H
#define COMPLEANNO_H

#include "alldayevent.h"

class BirthDay : public AllDayEvent {

private:
    Date dataNascita;

public:

    static const int ID = 4;

    Date getNascita() const;

    BirthDay(const Date& dataNasc,const std::string& nome,const std::string& descr,
             const std::string& luogo,
             const Date& dataEvento,const std::vector<std::string>& vettoreTag);

    BirthDay* clone() const;

    void serialize(QJsonObject &json) const;
};


#endif // COMPLEANNO_H
