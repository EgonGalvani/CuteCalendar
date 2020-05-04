#ifndef COMPLEANNO_H
#define COMPLEANNO_H

#include "alldayevent.h"

class BirthDay : public AllDayEvent {

private:

    Date dataNascita;
public:

    BirthDay(Date x,std::string nome,std::string descr,std::string luogo,
             Date data,std::vector<std::string>* vettoreTag);

    virtual void serialize();
    virtual Time getDuration();
    virtual bool isCompleted();


};


#endif // COMPLEANNO_H
