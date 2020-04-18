#ifndef WEEKLYRULE_H
#define WEEKLYRULE_H

#include "recurrencerule.h"
#include <vector>


class WeeklyRule : public RecurrenceRule {
private:
    std::vector<unsigned int> days;
};

#endif // WEEKLYRULE_H
