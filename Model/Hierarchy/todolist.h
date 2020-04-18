#ifndef TODOLIST_H
#define TODOLIST_H
#include "alldayevent.h"
#include "uniqueevent.h"

class ToDoList : public AllDayEvent,UniqueEvent {

    //Non so se usarla come classe privata,
    //il getter potrebbe rovinare il tutto
    class ListItem {
    private:
        std::string description;
        bool done;
    public:
        std::string getDescription;
        bool isDone();
        void setDone(bool);
        virtual void serialize();
        virtual ~ListItem();

    };

    std::vector<ListItem> items;

public:
    //getter setter
    std::vector<ListItem> getItems;
    void setDone(unsigned int);

    //Virtual methods
    virtual void serialize();
    virtual bool isCompleted();


};

#endif // TODOLIST_H
