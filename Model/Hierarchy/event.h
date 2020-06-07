#ifndef EVENTO_H
#define EVENTO_H
#include <string>
#include <vector>
#include "../DataType/time.h"
#include "../DataType/date.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QJsonDocument>
#include <sstream>


class Event {

private:
    std::string name;
    Date data;
    std::string description;
    std::string place;
    std::vector<std::string> tags;

public:

    Event(const std::string& nome,const std::string& descr,const std::string& luogo,
          const Date& date,const std::vector<std::string>& vettoreTag);

    //Pure virtual methods
    /**
     * @brief permette di clonare l'oggetto
     * @return il nuovo oggetto clone
     */
    virtual Event* clone() const = 0;

    /**
     * @brief permette di ottenere la durata tramite l'oggetto Time
     * @return la durata dell'evento in Time
     */
    virtual Time getDuration() const = 0;

    /**
     * @brief permette di sapere se l'evento è già avvenuto(quindi è già passata la data)
     * @return true se l'evento è già avvenuto
     */
    virtual bool isCompleted() const;


    /**
     * @brief permette di serializzare l'oggetto e le sue eventuali classe basi in formato json
     * @param json object che conterrà al suo interno la serializzazione
    */
    virtual void serialize(QJsonObject &json) const = 0;

    //Destructor
    /**
     * @brief Distruttore che si occupa di deallocare il necessario
     */
    virtual ~Event() = default;

    //Getter

    /**
     * @brief permette di ottenere il nome(titolo) dell'evento
     * @return nome dell'evento
     */
    std::string getName() const ;

    /**
     * @brief permette di ottenere la descrizione dell'evento
     * @return descrizione dell'evento
     */
    std::string getDesc() const ;

    /**
     * @brief permette di ottenere il luogo coinvolto nell'evento
     * @return luogo dell'evento
     */
    std::string getPlace() const ;

    /**
     * @brief permette di ottenere la data nel quale avviene l'evento
     * @return data dell'evento
     */
    Date getDate() const ;

    /**
     * @brief permette di ottenere il vettore di tag(stringhe) associate all'evento
     * @return vettore<stringhe> dei tag dell'evento
     */
    std::vector<std::string> getTags() const;

    //Setter

    /**
     * @brief permette di impostare il nome(titolo) dell'evento
     * @param nome evento
     */
    void setName(const std::string nome);

    /**
     * @brief permette di impostare la descrizione dell'evento
     * @param descrizione evento
     */
    void setDesc(const std::string desc);

    /**
     * @brief permette di impostare il luogo dell'evento
     * @param luogo evento
     */
    void setPlace(const std::string luogo);

    /**
     * @brief permette di impostare la data dell'evento
     * @param data evento
     */
    void setDate(const Date data);

    //Vector manipulation methods

    /**
     * @brief permette di aggiungere un nuovo tag al vettore di evento
     * @param il nuovo tag da inserire
     */
    void addTag(const std::string tag);

    /**
     * @brief permette di eliminare un tag
     * @param il tag da eliminare
     * @return il nuovo vettore con l'elemento rimosso
     */
    std::vector<std::string> deleteTag(const std::string tag);

    /**
     * @brief permette di sapere se il vettore contiene il tag richiesto
     * @param il tag da ricercare
     * @return true se il tag richiesto è all'interno del vettore
     */
    bool hasTag(const std::string tag)const ;

    /**
     * @brief permette di sapere se il vettore dei tag contiene almeno un tag (Quindi non è vuoto)
     * @return true se il vettore non è vuoto
     */
    bool atLeastOneTag() const;

    void clearTags();





};
#endif // EVENTO_H
