#include "event.h"

std::string Event::getDesc() {return  description;}

std::string Event::getName() {return name;}

std::string Event::getPlace() {return place;}

Date Event::getDate() {return data;}

void Event::setDesc(std::string desc) {description = desc;}

void Event::setName(std::string nome) {name = nome;}

void Event::setPlace(std::string posto) {place = posto;}

void Event::setDate(Date x) {data = x;}

void Event::addTag(std::string tag) {
    tags->push_back(tag);
}
//restituire nuovo vettore?
std::vector<std::string>* Event::deleteTag(std::string tag) {
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
bool Event::hasTag(std::string tag) {
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

//Destructor
Event::~Event() {}

