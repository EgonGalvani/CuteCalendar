#ifndef COMPLEANNO_H
#define COMPLEANNO_H

#include "alldayevent.h"

class BirthDay : public AllDayEvent {

private:

    Date dataNascita;
public:
    virtual void serialize();

    BirthDay(Date x,std::string nome,std::string descr,std::string luogo,
             Date data,std::vector<std::string>* vettoreTag);

};

#endif // COMPLEANNO_H
