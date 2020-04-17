#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H
#include <QTime>

class TimeManager {
public:
    virtual QTime* getDuration() = 0;
    virtual ~TimeManager();
};

#endif // TIMEMANAGER_H
