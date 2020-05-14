#ifndef EVENTO_H
#define EVENTO_H
#include <string>
#include <vector>
#include "../DataType/time.h"
#include "../DataType/date.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QJsonDocument>
#include <sstream>


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

    //Destructor
    virtual ~Event();

    //Getter
    std::string getName() const ;
    std::string getDesc() const ;
    std::string getPlace() const ;
    Date getDate() const ;
    std::vector<std::string>* getTags() const;

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


    static Event* parse(QJsonObject &json) {

        QJsonDocument doc(json);
        QString strJson(doc.toJson(QJsonDocument::Compact));
        std::cout<<strJson.toStdString();

        //USO stoi e non .toInt perchè toInt ritorna sempre valore di default
        int x = std::stoi(json["ID"].toString().toStdString());
        std::cout<<std::endl<<x<<std::endl;
        std::string nome;
        Date date;
        std::string descr;
        std::string place;
        std::vector<std::string>* tags;
        int urg;
        int act;
        std::vector<std::string> vectPart;
        Time start;
        Time end;
        Date birth;
        Time alert;
        bool rep;
        std::istringstream temp;
        std::string me;
        //MANCA TODOLIST

        //
        switch (x) {
        case 0:
            break;
        case 1:
            //REMINDER = 1
             /* int x,Time start,Time end,Time alert,bool rep,std::string nome,
                       std::string descr,std::string luogo,Date data,std::vector<std::string>* tags

                       */
            nome = json["NAME"].toString().toStdString();
            descr = json["DESCRIPTION"].toString().toStdString();
            place = json["PLACE"].toString().toStdString();
            //conversione stringa -> data
            std::cout<<std::endl<<json["DATA"].toString().toStdString()<<std::endl;
            temp= std::istringstream(json["DATA"].toString().toStdString());
            temp>>date;
            //json["TAGS"].
            me = json["TAGS"].toString().toStdString();
            std::cout<<std::endl<<me<<std::endl;
            rep = json["REPEAT"].toBool();
            //conversione stringa -> time
            temp= std::istringstream(json["START_TIME"].toString().toStdString());
            temp>>start;
            temp= std::istringstream(json["END_TIME"].toString().toStdString());
            temp>>end;
            temp= std::istringstream(json["ALERT_TIME"].toString().toStdString());
            temp>>alert;
            urg = json["URGENCY"].toInt();
            tags = new std::vector<std::string>();
            tags->push_back(me);
            return nullptr;
            //return new Reminder(urg,start,end,alert,rep,nome,descr,place,date,tags);
            break;

        case 2:
            break;
        case 3:
            break;
        }

        return nullptr;
    }


};
#endif // EVENTO_H
