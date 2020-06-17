#ifndef REMINDER_H
#define REMINDER_H

#include "eventwithduration.h"
#include "alert.h"

class Reminder : public EventWithDuration, public Alert {
private:
    unsigned int _urgency;
public:

    void setUrgency(const unsigned int& urg);

    /**
     * @brief ID univoco dell'evento
     */
    static const int ID = 1;

    Reminder(const unsigned int& urgency,const Time& start,const Time& end,
             const Time& alert, bool rep, const std::string& nome,
             const std::string& descr,const std::string& luogo,
             const Date& _data, const std::vector<std::string>& tag);

    /**
     * @brief permette di ottenere la priorita/urgenza dell'evento
     * @return la priorità dell'evento
     */
    unsigned int getUrgency()const ;

    //virtual
    /**
     * @brief permette di serializzare l'oggetto e le sue eventuali classe basi in formato json
     * @param json object che conterrà al suo interno la serializzazione
    */
    void serialize(QJsonObject &json)const ;

    /**
     * @brief permette di clonare l'oggetto
     * @return il nuovo oggetto clone
     */
    Reminder* clone()const ;

    /**
     * @brief Distruttore che si occupa di deallocare il necessario
     */
    virtual ~Reminder() = default;
};

#endif // REMINDER_H
