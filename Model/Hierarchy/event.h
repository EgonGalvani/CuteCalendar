#ifndef EVENTO_H
#define EVENTO_H
#include <string>
#include <vector>
#include "../DataType/time.h"
#include "../DataType/date.h"
#include <QJsonObject>
#include <QJsonArray>
class Event {

private:
    std::string name;
    Date data;
    std::string description;
    std::string place;
    std::vector<std::string>* tags;

public:

    Event(std::string nome,std::string descr,std::string luogo, Date data,
            std::vector<std::string>* vettoreTag);

    //Pure virtual methods
    virtual Event* clone() const = 0;

    virtual Time getDuration() const = 0;
    virtual bool isCompleted() const;
    virtual void serialize(QJsonObject &json) const = 0;
    static Event* parse();

    //Destructor
    virtual ~Event();

    //Getter
    std::string getName() const ;
    std::string getDesc() const ;
    std::string getPlace() const ;
    Date getDate() const ;
    std::vector<std::string>* getTags() const;
    QJsonObject toJson() const;

    //Setter
    void setName(const std::string x);
    void setDesc(const std::string x);
    void setPlace(const std::string x);
    void setDate(const Date x);

    //Vector manipulation methods


    //chiedere ad Egon se preferisce un bool per conferma o usiamo exeption
    void addTag(const std::string tag);
    //restituire nuovo vettore?
    std::vector<std::string>* deleteTag(const std::string tag);
    bool hasTag(const std::string tag)const ;

};
#endif // EVENTO_H
