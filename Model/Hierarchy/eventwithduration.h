#ifndef EVENTWITHDURATION_H
#define EVENTWITHDURATION_H

#include "event.h"

class EventWithDuration : virtual public Event {
    Time startTime;
    Time endTime;

public:
    //virtual
    /**
     * @brief permette di ottenere la durata tramite l'oggetto Time
     * @return la durata dell'evento in Time
     */
    Time getDuration()const ;

    /**
     * @brief permette di sapere se l'evento è già avvenuto(quindi è già passata la data)
     * @return true se l'evento è già avvenuto
     */
    bool isCompleted()const ;

    /**
     * @brief permette di serializzare l'oggetto e le sue eventuali classe basi in formato json
     * @param json object che conterrà al suo interno la serializzazione
    */
    void serialize(QJsonObject &json) const;

    EventWithDuration(const Time& start,const Time& end,
                      const std::string& nome = "",const std::string& descr = "",
                      const std::string& luogo = "",const Date& data = Date(),
                      const std::vector<std::string>& tags = std::vector<std::string>());

    //GETTER SETTER
    /**
     * @brief permette di ottenere il Time(orario) di inizio evento
     * @return Time dell'inizio evento
     */
    Time getStartTime()const ;

    /**
     * @brief permette di ottenere il Time(orario) di fine evento
     * @return Time della fine evento
     */
    Time getEndTime()const ;

    /**
     * @brief permette di impostare il Time(orario) di inizio evento
     * @param Time che rappresenta l'orario di inizio evento
     */
    void setStartTime(const Time start);

    /**
     * @brief permette di impostare il Time(orario) di fine evento
     * @param Time che rappresenta l'orario di fine evento
     */
    void setEndTime(const Time end);


    /**
     * @brief Distruttore che si occupa di deallocare il necessario
     */
    virtual ~EventWithDuration() = default;


};

#endif // EVENTWITHDURATION_H
