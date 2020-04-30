#ifndef MODEL_H
#define MODEL_H

#include "Container/vector.h"
#include "DataType/deepptr.h"
#include "DataType/date.h"
#include "Hierarchy/event.h"

#include <vector>

class Model {
private:
    // Container<Date, std::vector<DeepPtr<Event>>> _container;
public:
    Model() = default;
    ~Model() = default;

    // file
    void loadFromFile(const std::string&);
    void saveInFile(const std::string&) const;

    /* esempi di funzioni future ...
    void addEvent();
    void deleteEvent();
    std::vector<Event*> getEventsIn(const Date&) const;
    */
};

#endif // MODEL_H
