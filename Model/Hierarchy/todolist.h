#ifndef TODOLIST_H
#define TODOLIST_H

#include "alldayevent.h"

class ToDoList : public AllDayEvent {

private:
    //Non so se usarla come classe privata,
    //il getter potrebbe rovinare il tutto
    class ListItem {
        friend ToDoList;
    private:
        std::string _description;
        bool _done;
    public:

        ListItem(const std::string&, bool = true);

        /**
         * @brief permette di ottenere la descrizione dell'item
         * @return la descrizione dell'item
         */
        std::string getDescription()const ;

        /**
         * @brief permette di capire se l'item della lista è completato
         * @return true se è completato
         */
        bool isDone()const ;

        /**
         * @brief permette di impostare se l'item della lista è completato
         */
        void setDone(const bool);

        /**
         * @brief permette di serializzare l'oggetto e le sue eventuali classe basi in formato json
         * @param json object che conterrà al suo interno la serializzazione
        */
        void serialize(QJsonObject& json) const;
    };

    std::vector<ListItem> items;

public:

    static const int ID = 5;
    //getter setter

    /**
     * @brief getItems get every item inside the todolist
     * @return a vector containing listitem
     */
    std::vector<ListItem> getItems() const;

    /**
     * @brief addItem a single item to the todolist
     */
    void addItem(const std::string&, bool = false);


    /**
     * @brief addItems a vector of items to the todolist
     * @param items vector <string,bool>
     */
    void addItems(std::vector<std::pair<std::string,bool>>* items);

    void clear();

    //Virtual methods
    /**
     * @brief permette di clonare l'oggetto
     * @return il nuovo oggetto clone
     */
    ToDoList* clone()const ;

    /**
     * @brief permette di ottenere la durata tramite l'oggetto Time
     * @return la durata dell'evento in Time
     */
    Time getDuration()const ;

    /**
     * @brief permette di serializzare l'oggetto e le sue eventuali classe basi in formato json
     * @param json object che conterrà al suo interno la serializzazione
    */
    void serialize(QJsonObject &json)const ;

    /**
     * @brief permette di sapere se l'evento è già avvenuto(quindi è già passata la data)
     * @return true se l'evento è già avvenuto
     */
    bool isCompleted() const;

    ToDoList(const std::string& nome,const std::string& descr,
             const std::string& luogo,
             const Date& dataEvento,const std::vector<std::string>& vettoreTag,
             std::vector<std::pair<std::string,bool>>* items = nullptr);

};

#endif // TODOLIST_H
