#ifndef DATEMANAGER_H
#define DATEMANAGER_H
#include <QDate>
#include <iostream>
#include <map>

//MOMENTANEO
#include "event.h"

class DateManager {
public:
    //Ho bisogno di un vettore?Come capisco se la data è quella?è un metodo virtuale puro forse?
    //SI CHE LO È DEMENTE CHE NON SEI ALTRO,È UNA INTERFACCIA
    virtual bool isToday(QDate* today) = 0;
    virtual bool hasEventInInterval(QDate* start,QDate end) = 0;
    virtual std::multimap<QDate*,Event*> getEventsInInterval(QDate* start,QDate* end) = 0;

    virtual ~DateManager();
};

#endif // DATEMANAGER_H
