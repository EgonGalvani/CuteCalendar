#ifndef EVENTO_H
#define EVENTO_H
#include <string>
#include <vector>
#include "../DataType/time.h"
#include "../DataType/date.h"
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
    virtual Event* clone() = 0;

    virtual Time getDuration() = 0;
    virtual bool isCompleted();
    virtual void serialize() = 0;
    static Event* parse();

    //Destructor
    virtual ~Event();

    //Getter
    std::string getName();
    std::string getDesc();
    std::string getPlace();
    Date getDate();

    //Setter
    void setName(std::string x);
    void setDesc(std::string x);
    void setPlace(std::string x);
    void setDate(Date x);

    //Vector manipulation methods


    //chiedere ad Egon se preferisce un bool per conferma o usiamo exeption
    void addTag(std::string tag);
    //restituire nuovo vettore?
    std::vector<std::string>* deleteTag(std::string tag);
    bool hasTag(std::string tag);

};
#endif // EVENTO_H
