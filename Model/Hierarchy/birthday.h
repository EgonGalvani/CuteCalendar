#ifndef COMPLEANNO_H
#define COMPLEANNO_H

#include "alldayevent.h"

class BirthDay : public AllDayEvent {

private:

    Date dataNascita;
public:

    BirthDay(Date x,std::string nome,std::string descr,std::string luogo,
             Date data,std::vector<std::string>* vettoreTag);

    BirthDay* clone() const;

    void serialize(QJsonObject &json) const;


};


#endif // COMPLEANNO_H
