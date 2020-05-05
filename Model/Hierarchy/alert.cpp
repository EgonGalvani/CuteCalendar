#include "alert.h"

Alert::Alert(Time x, bool y)
    : alertTime(x),repeat(y){}


void Alert::setAlertTime(Time x) {alertTime=x;}
void Alert::setRepeat(bool x) {repeat=x;}

Time Alert::getAlertTime() {return alertTime;}
bool Alert::doesRepeat() {return repeat;}
