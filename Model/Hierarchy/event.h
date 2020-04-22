#ifndef EVENTO_H
#define EVENTO_H
#include <string>
#include <vector>
class Event {

private:
    std::string name;
    std::string description;
    std::string place;
    std::vector<std::string> tags;

public:

    Event(std::string nome,std::string descr,std::string luogo,
            std::vector<std::string> vettoreTag);

    //Pure virtual methods
    virtual Event* clone() = 0;
    virtual void serialize() = 0;
    virtual bool isCompleted() = 0;

    //Destructor
    virtual ~Event();

    //Getter
    std::string getName();
    std::string getDesc();
    std::string getPlace();

    //Setter
    void setName();
    void setDesc();
    void setPlace();

    //Vector manipulation methods


    //chiedere ad Egon se preferisce un bool per conferma o usiamo exeption
    void addTag(std::string tag);
    //restituire nuovo vettore?
    void deleteTag(std::string tag);
    bool hasTag(std::string tag);

};
#endif // EVENTO_H
