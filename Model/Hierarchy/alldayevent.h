#ifndef ALLDAYEVENT_H
#define ALLDAYEVENT_H


#include "event.h"

class AllDayEvent :virtual public Event{
private:
public:
    AllDayEvent(const std::string& nome = "",const std::string& descr = ""
            ,const std::string& luogo = "", const Date& data = Date(),
                             const std::vector<std::string>& tags = std::vector<std::string>());

    /**
     * @brief permette di ottenere la durata tramite l'oggetto Time
     * @return la durata dell'evento in Time
     */
    Time getDuration() const;

    /**
     * @brief permette di serializzare l'oggetto e le sue eventuali classe basi in formato json
     * @param json object che conterrà al suo interno la serializzazione
    */
    void serialize(QJsonObject &json) const;

    /**
     * @brief Distruttore che si occupa di deallocare il necessario
     */
    virtual ~AllDayEvent() = default;

};

#endif // ALLDAYEVENT_H
