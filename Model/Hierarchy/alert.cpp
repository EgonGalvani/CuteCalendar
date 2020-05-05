#include "alert.h"

Alert::Alert(Time x, bool y,std::string nome,std::string descr,std::string luogo, Date data,
             std::vector<std::string>* tags)
    : Event(nome,descr,luogo,data,tags),
      alertTime(x),repeat(y){}


void Alert::setAlertTime(Time x) {alertTime=x;}
void Alert::setRepeat(bool x) {repeat=x;}

Time Alert::getAlertTime() {return alertTime;}
bool Alert::doesRepeat() {return repeat;}
