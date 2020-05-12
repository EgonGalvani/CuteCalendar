#include "model.h"

bool Model::hasEvent(const Date& d) const {
    return _data.bucket_size(d) > 0;
}

Model::It Model::insertEvent(const Date& d, Event* e) {
    return _data.insert(_data.find(d), DeepPtr<Event>(e));
}

void Model::removeEvent(const Date& date, const It& it) {
    _data.erase(_data.find(date), it);
}

std::vector<Model::It> Model::getEvents(const Date &d) {
    std::vector<It> its;

    if(hasEvent(d))
        for(It it = _data.begin(d); it != _data.end(d); it++)
            its.push_back(it);
    return its;
}


