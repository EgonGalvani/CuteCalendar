#ifndef MODEL_H
#define MODEL_H

#include "DataType/deepptr.h"
#include "DataType/date.h"
#include "Container/vector.h"
#include "Hierarchy/event.h"
#include "Container/unorderedmultimap.h"

#include <vector>

class Model {
private:
    UnorderedMultimap<Date, DeepPtr<Event>> _data;

public:
    // per costruttori e distruttori vanno bene quelli standard
    Model() = default;

    // tipo di iteratore usato all'esterno del model
    using It = UnorderedMultimap<Date, DeepPtr<Event>>::LocalIterator;

    void loadFromFile(const std::string&);
    void saveInFile(const std::string&) const;

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
    It insertEvent(const Date& d, Event* e);

    /**
     * @brief permette di rimuovere un elemento dal container
     * @param d: data dell'evento
     * @param it: iteratore che si riferisce all'evento che si vuole rimuovere
     */
    void removeEvent(const Date& d, const It& it);
};

#endif // MODEL_H
