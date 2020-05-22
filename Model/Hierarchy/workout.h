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

    Workout(const int& attivita,const Time& start,const Time& end,
            const std::string& nome,const std::string& descr,
            const std::string& luogo,const Date& data,
            const std::vector<std::string>& tags);
    activity getSport() const ;
    void setSport(const int x);

    //virtual methods
    Workout* clone()const ;
    void serialize(QJsonObject &json)const ;
    virtual ~Workout();

};


#endif // TRAINING_H
