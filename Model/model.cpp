#include "model.h"

void Model::loadFromFile(const std::string& fileName) {

}

void Model::saveInFile(const std::string& fileName) const {
   /* XMLFileIO xmlFileIO(fileName);
    for(auto it = _container.cbegin(); it != _container.cend(); it++) {
        // xmlFileIO.write() info about the day es: <Date ... >


        std::vector<DeepPtr<Event>> events = it->getInfo();
        for(auto iit = events.cbegin(); iit != events.cend(); iit++) {
            iit->serialize(QStreamWriter);
        }
    }*/
}

bool Model::hasEvent(const Date& d) const {
    return _data.bucket_size(d) > 0;
}

Model::It Model::insertEvent(const Date& d, Event* e) {
    return _data.insert(_data.find(d), DeepPtr<Event>(e));
}

void Model::removeEvent(const Date& date, const It& it) {
    // _data.erase(_data.find(date), it);
}

