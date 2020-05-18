#include "model.h"

bool Model::hasEvent(const Date& d) const {
    return _data.bucket_size(d) > 0;
}

Model::It Model::insertEvent(Event* e) {
    const Date eventDate = e->getDate();

    /* NOTA: quando il deepptr (temporaneo anonimo) viene distrutto
        allora viene distrutto anche l'evento e. Nell'iteratore ci sarà
        un oggetto ottenuto tramite una clone. Per questo è necessario mem*/
    auto bucketIt = _data.insert(eventDate, DeepPtr<Event>(e));
    return --_data.end(*bucketIt);
}

void Model::removeEvent(const It& it) {
    _data.erase(_data.find( (*it)->getDate()), it);
}

std::vector<Model::It> Model::getEvents(const Date &d) {
    std::vector<It> its;

    if(hasEvent(d))
        for(It it = _data.begin(d); it != _data.end(d); it++)
            its.push_back(it);
    return its;
}


