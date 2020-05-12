#include "event.h"

std::string Event::getDesc() const{return  description;}

std::string Event::getName() const{return name;}

std::string Event::getPlace() const{return place;}

Date Event::getDate() const{return data;}

void Event::setDesc(const std::string desc) {description = desc;}

void Event::setName(const std::string nome) {name = nome;}

void Event::setPlace(const std::string posto) {place = posto;}

void Event::setDate(const Date x) {data = x;}

void Event::addTag(const std::string tag) {
    tags->push_back(tag);
}
//restituire nuovo vettore?
std::vector<std::string>* Event::deleteTag(const std::string tag) {
    std::vector<std::string>::iterator it = tags->begin();
    while (it!=tags->end()) {
        if ((*it)==tag) {
            it = tags->erase(it);
        }else {
            ++it;
        }
    }
    return tags;
}
bool Event::hasTag(const std::string tag) const {
    bool found = false;
    for (std::vector<std::string>::iterator it = tags->begin();!found && it!=tags->end();++it) {
        found = *it==tag;
    }
    return found;
}

Event::Event(std::string nome,std::string descr,std::string luogo,Date dt,
             std::vector<std::string>* vettoreTag) : name(nome),data(dt),
             description(descr),place(luogo),tags(vettoreTag) {
}

bool Event::isCompleted() const {
    return data<=Date();
}

//Destructor
Event::~Event() {}

