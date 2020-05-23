#ifndef MEETING_H
#define MEETING_H

#include "eventwithduration.h"
#include "alert.h"

class Meeting : public EventWithDuration, public Alert {
private:
    std::vector<std::string> partEmails;

public:

    /**
     * @brief ID univoco dell'evento
     */
    static const int ID = 3;



    Meeting(const std::vector<std::string>& part,const Time& start,
            const Time& end,const Time& alert,const bool& repeat,
            const std::string& nome,const std::string& descr,
            const std::string& luogo,const Date& data,
            const std::vector<std::string>& vettoreTag);

    /**
     * @brief permette di ottenere il vettore delle mail dei partecipanti
     * @return il vettore delle mail dei partecipanti
     */
    std::vector<std::string> getPartecipants() const;


    /**
     * @brief permette di aggiungere un nuovo partecipante al vettore di evento
     * @param il nuovo partecipante da inserire
     */
    void addPartecipant(const std::string tag);

    /**
     * @brief permette di eliminare un partecipante
     * @param il partecipante da eliminare
     * @return il nuovo vettore con l'elemento rimosso
     */
    std::vector<std::string> deletePartecipant(const std::string tag);

    /**
     * @brief permette di sapere se il vettore contiene il partecipante richiesto
     * @param il partecipante da ricercare
     * @return true se il partecipante richiesto è all'interno del vettore
     */
    bool hasPartecipant(const std::string tag)const ;

    /**
     * @brief permette di sapere se il vettore dei tag contiene almeno un partecipante (Quindi non è vuoto)
     * @return true se il vettore non è vuoto
     */
    bool atLeastOnePartecipant() const;

    //virtual

    /**
     * @brief permette di clonare l'oggetto
     * @return il nuovo oggetto clone
     */
    Meeting* clone()const ;

    /**
     * @brief permette di serializzare l'oggetto e le sue eventuali classe basi in formato json
     * @param json object che conterrà al suo interno la serializzazione
    */
    void serialize(QJsonObject &json)const ;

    /**
     * @brief Distruttore che si occupa di deallocare il necessario
     */
    virtual ~Meeting() = default;
};

#endif // MEETING_H
