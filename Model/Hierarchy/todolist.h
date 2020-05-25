#ifndef TODOLIST_H
#define TODOLIST_H

#include "alldayevent.h"

class ToDoList : public AllDayEvent {

private:
    //Non so se usarla come classe privata,
    //il getter potrebbe rovinare il tutto
    class ListItem {
    private:
        std::string description;
        bool done;
    public:

        ListItem(const std::string& = "", bool = true);

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
    };

    std::vector<ListItem> items;

public:
    //getter setter
    std::vector<ListItem> getItems() const;

    //praticamente quando vado ad aggiungere
    //devo costruire un nuovo item
    //Ma devo mettere un id univoco?For reference chat telegram 21 aprile
    void addItem(const std::string&, bool = false);

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
    bool isCompleted()const ;
};

#endif // TODOLIST_H
