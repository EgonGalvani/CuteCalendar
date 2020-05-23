#include "event.h"

std::string Event::getDesc() const{return  description;}

std::string Event::getName() const{return name;}

std::string Event::getPlace() const{return place;}

Date Event::getDate() const{return data;}

std::vector<std::string> Event::getTags() const {return tags;}

void Event::setDesc(const std::string desc) {description = desc;}

void Event::setName(const std::string nome) {name = nome;}

void Event::setPlace(const std::string posto) {place = posto;}

void Event::setDate(const Date x) {data = x;}

void Event::addTag(const std::string tag) {
    tags.push_back(tag);
}
//restituire nuovo vettore?
std::vector<std::string> Event::deleteTag(const std::string tag) {
    std::vector<std::string>::iterator it = tags.begin();
    while (it!=tags.end()) {
        if ((*it)==tag) {
            it = tags.erase(it);
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
             const Date& date,const std::vector<std::string>& vettoreTag) : name(nome),data(date),
             description(descr),place(luogo),tags(vettoreTag) {
}

bool Event::isCompleted() const {
    return data<=Date();
}

void Event::serialize(QJsonObject &json) const {
    json["ID"] = 0;
    json["NAME"] = QString::fromStdString(getName());
    json["DATA"] = QString::fromStdString(getDate().toString());
    json["DESCRIPTION"] = QString::fromStdString(getDesc());
    json["PLACE"] = QString::fromStdString(getPlace());

    QJsonArray tagArray;
    if (!tags.empty()) {
        std::vector<std::string> temp = tags;

        foreach (const std::string tag, temp) {
            tagArray.append(QString::fromStdString(tag));
        }
    }
    json["TAGS"] = tagArray;
}


