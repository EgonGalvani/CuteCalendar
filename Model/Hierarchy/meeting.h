#ifndef MEETING_H
#define MEETING_H

#include "preciseevent.h"

class Meeting : public PreciseEvent {
private:
    std::vector<std::string> partEmails;

public:

    std::vector<std::string> getPartecipants();
    virtual void serialize();

};

#endif // MEETING_H
