#include "alert.h"

Alert::Alert(const Time& alertTime,const bool& ripete,const std::string& nome,
             const std::string& descr,const std::string& luogo,const Date& data,
             const std::vector<std::string>& tags)
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
