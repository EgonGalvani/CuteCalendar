#ifndef FACTORY_H
#define FACTORY_H

#include "birthday.h"
#include "meeting.h"
#include "reminder.h"
#include "workout.h"
#include "todolist.h"
#include <regex>

class Factory {

private:


    QJsonObject json;

    Date date;
    std::string nome;
    std::string descr;
    std::string place;
    QJsonArray tmp;
    std::vector<std::string>tags;
    unsigned int urg;
    int act;
    std::vector<std::string> vectPart;
    Time start;
    Time end;
    unsigned short birth;
    Time alert;
    bool rep;
    std::istringstream temp;
    int id;

    /**
     * @brief primo passaggio del parse
     */
    void firstParse();

    /**
     * @brief secondo passaggio del parse
     */
    void secondParse();

    /**
     * @brief checks if the json object has invalid fields,can throw exception
     */
    void firstCheck() const;

    /**
     * @brief isEmail checks if the email has a valid format (es dgiac@gmail.com)
     * @param email to check
     * @return true if email has a valid format
     */
    bool isEmail(const std::string& email) const;

public:

    /**
     * @brief Costruttore di Factory
     * @param il json dal quale estrapolare l'evento
     */
    Factory(QJsonObject &js);

    /**
     * @brief funzione che permette di estrapolare l'evento dal json passato nel costruttore
     * @return un puntatore all'evento estrapolato
     */
    Event* parse();
};

#endif // FACTORY_H
