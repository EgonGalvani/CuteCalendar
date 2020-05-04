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
        ListItem(std::string = nullptr,bool = false);
        std::string getDescription();
        bool isDone();
        void setDone(bool);
    };

    std::vector<ListItem> items;

public:
    //getter setter
    std::vector<ListItem> getItems();

    //praticamente quando vado ad aggiungere
    //devo costruire un nuovo item
    //Ma devo mettere un id univoco?For reference chat telegram 21 aprile
    void addItem();



    //Virtual methods
    virtual void serialize();
    virtual bool isCompleted();


};

#endif // TODOLIST_H
