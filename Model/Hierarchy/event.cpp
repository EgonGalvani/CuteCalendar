#include "event.h"

std::string Event::getDesc() {return  description;}

std::string Event::getName() {return name;}

std::string Event::getPlace() {return place;}

void Event::addTag(std::string tag) {
    tags.push_back(tag);
}
//restituire nuovo vettore?
void Event::deleteTag(std::string tag) {
    std::vector<std::string>::iterator it = tags.begin();
    while (it!=tags.end()) {
        if ((*it)==tag) {
            it = tags.erase(it);
        }else {
            ++it;
        }
    }
}
bool Event::hasTag(std::string tag) {
    bool found = false;
    for (std::vector<std::string>::iterator it = tags.begin();!found && it!=tags.end();++it) {
        found = *it==tag;
    }
}

Event::Event(std::string nome,std::string descr,std::string luogo,
             std::vector<std::string> vettoreTag) : name(nome),description(descr),
             place(luogo),tags(vettoreTag) {
}

Event* Event::clone() {

}

//Destructor
Event::~Event() {}

