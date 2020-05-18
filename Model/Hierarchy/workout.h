#ifndef TRAINING_H
#define TRAINING_H

#include "eventwithduration.h"

class Workout : public EventWithDuration {
private:

    enum activity {
        Calcio = 0,
        Pallavolo,
        Nuoto,
        Palestra,
    };

    activity act;

public:

    static const int ID = 2;

    Workout(int x,Time start,Time end,std::string nome,std::string descr,
            std::string luogo,Date data,std::vector<std::string>* vettoreTag);
    activity getSport() const ;
    void setSport(const int x);

    //virtual methods
    Workout* clone()const ;
    void serialize(QJsonObject &json)const ;
    virtual ~Workout();

};


#endif // TRAINING_H
