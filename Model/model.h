#ifndef MODEL_H
#define MODEL_H

#include "DataType/deepptr.h"
#include "DataType/date.h"
#include "Container/vector.h"
#include "Hierarchy/factory.h"
#include "Container/unorderedmultimap.h"
#include <QJsonDocument>

#include <vector>

class Model {
private:
    UnorderedMultimap<Date, DeepPtr<Event>> _data;

    /**
     * @brief permette di estrapolare dal json il contenuto del model
     * @param l'oggetto contenente i dati da estrapolare
     */
    void parse(QJsonObject &json);

    /**
     * @brief permette di serializzare il model e salvare i dati nel json
     * @param oggetto nel quale viene salvato il contenuto del model
     */
    void serialize(QJsonObject &json) const;

public:
    // per costruttori e distruttori vanno bene quelli standard
    Model() = default;

    // tipo di iteratore usato all'esterno del model
    using It = UnorderedMultimap<Date, DeepPtr<Event>>::LocalIterator;

    /**
     * @brief permette di riempire il model di eventi presi dal file
     * @param  la destinazione del file dal quale caricare i dati
     */
    void loadFromFile(const QString& = "data.json");

    /**
     * @brief permette di salvare su file il contenuto del model(serialize & salvataggio su disco)
     * @param la destinazione del file nel quale salvare
     */
    void saveInFile(const QString& = "data.json") const;

    /**
     * @brief permette di verificare la presenza di eventi per una data specificata
     * @param d: data di interesse
     * @return true sse sono pianificati degli eventi per la data d
     */
    bool hasEvent(const Date& d) const;

    /**
     * @brief permette di ottenere tutti gli eventi presenti in una specifica data
     * @param d: data di interesse
     * @return un vettore di iteratori ai vari eventi presenti in data d
     */
    std::vector<It> getEvents(const Date& d);

    /**
     * @brief permette di inserire un evento in una specifica data
     * @param d: data di interesse
     * @param e: evento da inserire
     * @return iteratore all'elemento inserito
     */
    It insertEvent(Event* e);

    /**
     * @brief permette di rimuovere un elemento dal container
     * @param d: data dell'evento
     * @param it: iteratore che si riferisce all'evento che si vuole rimuovere
     */
    void removeEvent(const It& it);
};

#endif // MODEL_H
