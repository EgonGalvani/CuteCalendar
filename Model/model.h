#ifndef MODEL_H
#define MODEL_H

#include "DataType/deepptr.h"
#include "DataType/date.h"
#include "Hierarchy/event.h"
#include "Container/unorderedmultimap.h"

class Model {
private:
    UnorderedMultimap<Date, DeepPtr<Event>> _data;

public:
    Model() = default;
    ~Model() = default;

    using It = UnorderedMultimap<Date, DeepPtr<Event>>::LocalIterator;

    void loadFromFile(const std::string&);
    void saveInFile(const std::string&) const;

    bool hasEvent(const Date&) const;
    std::vector<DeepPtr<Event>> getEvents(const Date&) const;

    // mi servirebbe un iterator al nuovo elemento inserito
    It insertEvent(const Date&, Event*);

    void removeEvent(const Date& d, const It&); // da vedere se Date o Date
};

#endif // MODEL_H
