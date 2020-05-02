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

    // file
    void loadFromFile(const std::string&);
    void saveInFile(const std::string&) const;

    bool hasEventInDate(const Date&) const;
    void insertEventInDate(const Date&, Event*);
};

#endif // MODEL_H
