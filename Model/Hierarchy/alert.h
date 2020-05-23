#ifndef ALERT_H
#define ALERT_H
#include "event.h"

class Alert :virtual public Event{
private:
    Time alertTime;
    bool repeat;
public:

    Alert(const Time& alertTime,const bool& repeat,const std::string& nome = "",
          const std::string& descr = "",const std::string& luogo = "",const Date& data = Date(),
                             const std::vector<std::string>& tags = std::vector<std::string>());

    /**
     * @brief permette di impostare l'orario nel quale viene attivata l'allerta
    */
    void setAlertTime(const Time alertTime);

    /**
     * @brief permette di impostare se l'allerta viene ripetuta più volte(true)
    */
    void setRepeat(const bool repeat);

    /**
     * @brief permette di ottenere l'orario dell'allerta
     * @return orario(Time) dell'allerta
    */
    Time getAlertTime() const;

    /**
     * @brief permette di sapere se l'allerta viene ripetuta
     * @return true se l'allerta viene ripetuta
    */
    bool doesRepeat() const;


    /**
     * @brief permette di serializzare l'oggetto e le sue eventuali classe basi in formato json
     * @param json object che conterrà al suo interno la serializzazione
    */
    void serialize(QJsonObject &json) const;

    /**
     * @brief Distruttore che si occupa di deallocare il necessario
     */
    virtual ~Alert() = default;


};

#endif // ALERT_H
