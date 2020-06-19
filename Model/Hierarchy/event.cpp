#include "event.h"

std::string Event::getDesc() const{return  _description;}

std::string Event::getName() const{return _name;}

std::string Event::getPlace() const{return _place;}

Date Event::getDate() const{return Date(_data);}

std::vector<std::string> Event::getTags() const {return tags;}

void Event::setDesc(const std::string desc) {_description = desc;}

void Event::setName(const std::string nome) {_name = nome;}

void Event::setPlace(const std::string posto) {_place = posto;}

void Event::setDate(const Date x) {_data = x;}

void Event::addTag(const std::string tag) {
    if (!hasTag(tag)) tags.push_back(tag);
}

void Event::clearTags() {
    tags.clear();
}

//restituire nuovo vettore?
std::vector<std::string> Event::deleteTag(const std::string tag) {
    std::vector<std::string>::iterator it = tags.begin();
    bool found = false;
    while (it!=tags.end() && !found) {
        if ((*it)==tag) {
            it = tags.erase(it);
            found = true;
        }else {
            ++it;
        }
    }
    return tags;
}
bool Event::hasTag(const std::string tag) const {
    bool found = false;
    for (std::vector<std::string>::const_iterator it = tags.begin();!found && it!=tags.end();++it) {
        found = *it==tag;
    }
    return found;
}

bool Event::atLeastOneTag() const {
    return !tags.empty();
}

Event::Event(const std::string& nome,const std::string& descr,const std::string& luogo,
             const Date& date,const std::vector<std::string>& vettoreTag) : _name(nome),_data(date),
             _description(descr),_place(luogo),tags(vettoreTag) {
}

void Event::serialize(QJsonObject &json) const {
    json["ID"] = 0;
    json["NAME"] = QString::fromStdString(getName());
    json["DESCRIPTION"] = QString::fromStdString(getDesc());
    json["PLACE"] = QString::fromStdString(getPlace());

    QJsonArray tagArray;
    //è una sorta di conversione,
    //da std::vector a qjsonArray
    if (!tags.empty()) {
        //Si itera il vettore prendendo ogni stringa al suo interno
        foreach (const std::string tag, tags) {
            //Si converte la stringa in qstring e la si inserisce nel qjsonarray
            tagArray.append(QString::fromStdString(tag));
        }
    }
    //Si inserisce il qjsonarray nel qjsonobject
    json["TAGS"] = tagArray;
}


