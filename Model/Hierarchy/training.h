#ifndef TRAINING_H
#define TRAINING_H
#include "recurrence.h"
#include "eventwithduration.h"

class Training : public Recurrence,EventWithDuration {
private:

    //Forse un enum?
    std::string sport;

public:
    std::string getSport();
    void setSport();

    virtual void serialize();

};


#endif // TRAINING_H
