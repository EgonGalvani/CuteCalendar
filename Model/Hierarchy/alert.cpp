#include "alert.h"

Alert::Alert(const Time& alertTime,const bool& ripete,const std::string& nome,
             const std::string& descr,const std::string& luogo,const Date& data,
             const std::vector<std::string>& tags)
    : Event(nome,descr,luogo,data,tags),
      _alertTime(alertTime),_repeat(ripete){}


void Alert::setAlertTime(const Time x) {_alertTime=x;}
void Alert::setRepeat(const bool x) {_repeat=x;}

Time Alert::getAlertTime() const{return _alertTime;}
bool Alert::doesRepeat() const{return _repeat;}

void Alert::serialize(QJsonObject &json) const{
    //chiamata alla classe base
    Event::serialize(json);

    //Conversione = Time->std::string->QString->QJSonValue
    json["ALERT_TIME"] = QString::fromStdString(_alertTime.toString());
    json["REPEAT"] = _repeat;
}

