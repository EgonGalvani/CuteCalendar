#ifndef TRAINING_H
#define TRAINING_H

#include "eventwithduration.h"

class Workout : public EventWithDuration {
private:

    enum activity {
        Calcio = 0,
        Pallavolo,
        Nuoto,
        Palestra,
    };

    activity act;

public:

    /**
     * @brief ID univoco dell'evento
     */
    static const int ID = 2;

    Workout(int attivita, const Time& start, const Time& end,
            const std::string& nome, const std::string& descr,
            const std::string& luogo, const Date& data,
            const std::vector<std::string>& tags);

    /**
     * @brief permette di ottenere l'attività coinvolta nel workout
     * @return l'attività del workout
     */
    activity getActivity() const ;

    /**
     * @brief permette di impostare l'attività del workout
     * @param l'attività da impostare
     */
    void setActivity(const int activity);

    //virtual methods
    /**
     * @brief permette di clonare l'oggetto
     * @return il nuovo oggetto clone
     */
    Workout* clone()const ;

    /**
     * @brief permette di serializzare l'oggetto e le sue eventuali classe basi in formato json
     * @param json object che conterrà al suo interno la serializzazione
    */
    void serialize(QJsonObject &json)const ;

    /**
     * @brief Distruttore che si occupa di deallocare il necessario
     */
    virtual ~Workout() = default;
};


#endif // TRAINING_H
