#include "recurrence.h"

/*
 *     QDate* startDate;
    QDate* endDate;
    RecurrenceRule* period;
*/
//Immagino chieda se data attuale>endDate?E magari altro che riguarda la regola di recurrence
bool Recurrence::isCompleted() {

}
bool Recurrence::isToday(QDate* day) {

}

//Logica giusta?Controllo se la mia data è dentro i confini dati
//ES | = confini; \= data
//  | \ \ | OK
// \ | \ | NO etc
bool Recurrence::isInInterval(QDate* beg,QDate* end) {
    return startDate>=beg && endDate<=end;
}

//Getter

//Intende ha una fine o è finito?
//Immagino ha una fine
bool Recurrence::hasEnd() {
    return endDate!=nullptr;
}
//Non so il metodo cosa chieda di fare
QDate* Recurrence::getNextEvent() {

}
