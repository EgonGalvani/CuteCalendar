#include "model.h"

bool Model::hasEvent(const Date& d) const {
    return _data.bucket_size(d) > 0;
}

Model::It Model::insertEvent(Event* e) {
    _data.insert(e->getDate(), DeepPtr<Event>(e));
    return --_data.end(e->getDate());
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


