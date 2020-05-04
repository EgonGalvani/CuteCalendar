#include "alert.h"

Alert::Alert(Time x,bool y,std::string nome,std::string descr,std::string luogo, Date data,
             std::vector<std::string>* vettoreTag)
    : Event(nome,descr,luogo,data,vettoreTag),
    alertTime(x),repeat(y){}

void Alert::setAlertTime(Time x) {alertTime=x;}
void Alert::setRepeat(bool x) {repeat=x;}

Time Alert::getAlertTime() {return alertTime;}
bool Alert::doesRepeat() {return repeat;}
