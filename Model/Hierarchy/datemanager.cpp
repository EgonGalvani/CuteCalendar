#include "datemanager.h"

bool DateManager::isToday(QDate* today) {}
bool DateManager::hasEventInInterval(QDate* start,QDate end) {}
std::multimap<QDate*,Event*> DateManager::getEventsInInterval(QDate* start,QDate* end) {}

DateManager::~DateManager(){}
