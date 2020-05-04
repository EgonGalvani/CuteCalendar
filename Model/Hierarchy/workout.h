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

    Workout(int x,Time start,Time end,std::string nome,std::string descr,
            std::string luogo,Date data,std::vector<std::string>* vettoreTag);
    activity getSport();
    void setSport(int x);

    virtual void serialize();

};


#endif // TRAINING_H
