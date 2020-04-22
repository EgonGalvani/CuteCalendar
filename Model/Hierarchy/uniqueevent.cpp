#include "uniqueevent.h"

//>=
bool UniqueEvent::isInInterval(QDate* start,QDate* end) {
    return date>=start && date<=end;
}
