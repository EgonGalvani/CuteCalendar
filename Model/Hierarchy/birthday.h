#ifndef COMPLEANNO_H
#define COMPLEANNO_H

#include "alldayevent.h"

class BirthDay : public AllDayEvent {

private:
    Date dataNascita;

public:

    /**
     * @brief ID univoco dell'evento
     */
    static const int ID = 4;



    BirthDay(const Date& dataNasc,const std::string& nome,const std::string& descr,
             const std::string& luogo,
             const Date& dataEvento,const std::vector<std::string>& vettoreTag);

    /**
     * @brief permette di ottenere la data di nascita
     * @return data di nascita
     */
    Date getNascita() const;

    //virtuali
    /**
     * @brief permette di clonare l'oggetto
     * @return il nuovo oggetto clone
     */
    BirthDay* clone() const;


    /**
     * @brief permette di serializzare l'oggetto e le sue eventuali classe basi in formato json
     * @param json object che conterrà al suo interno la serializzazione
    */
    void serialize(QJsonObject &json) const;

    /**
     * @brief Distruttore che si occupa di deallocare il necessario
     */
    virtual ~BirthDay() = default;
};


#endif // COMPLEANNO_H
