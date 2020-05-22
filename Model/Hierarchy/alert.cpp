#include "alert.h"

Alert::Alert(Time alertTime, bool ripete,std::string nome,std::string descr,std::string luogo, Date data,
             std::vector<std::string>* tags)
    : Event(nome,descr,luogo,data,tags),
      alertTime(alertTime),repeat(ripete){}


void Alert::setAlertTime(const Time x) {alertTime=x;}
void Alert::setRepeat(const bool x) {repeat=x;}

Time Alert::getAlertTime() const{return alertTime;}
bool Alert::doesRepeat() const{return repeat;}

void Alert::serialize(QJsonObject &json) const{
    Event::serialize(json);
    json.insert("ID","5");
    json["ALERT_TIME"] = QString::fromStdString(alertTime.toString());
    json["REPEAT"] = repeat;

}
