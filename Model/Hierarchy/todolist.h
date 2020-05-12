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
        ListItem(std::string = nullptr,bool = true);
        std::string getDescription()const ;
        bool isDone()const ;
        void setDone(const bool);
    };

    std::vector<ListItem> items;

public:
    //getter setter
    std::vector<ListItem> getItems() const;

    //praticamente quando vado ad aggiungere
    //devo costruire un nuovo item
    //Ma devo mettere un id univoco?For reference chat telegram 21 aprile
    void addItem(const std::string x,const bool done = false);




    //Virtual methods
    ToDoList* clone()const ;
    Time getDuration()const ;
    void serialize()const ;
    bool isCompleted()const ;


};

#endif // TODOLIST_H
