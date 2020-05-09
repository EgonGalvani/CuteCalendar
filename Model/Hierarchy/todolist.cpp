#include "todolist.h"

//METODI LIST ITEM

//std::vector<ListItem> items;

ToDoList::ListItem::ListItem(std::string x,bool y) : description(x),done(y) {}

std::string ToDoList::ListItem::getDescription() {
    return description;
}
bool ToDoList::ListItem::isDone() {
    return done;
}
void ToDoList::ListItem::setDone(bool x) {
    done = x;
}


//std::vector<ListItem*> getItems;
std::vector<ToDoList::ListItem> ToDoList::getItems() {
    return items;
}

ToDoList* ToDoList::clone() {
    return new ToDoList(*this);
}

//Virtual methods
//Controlla ogni elemento del vettore se è done;
bool ToDoList::isCompleted() {
    bool found = true;
    for (std::vector<ListItem>::iterator x= items.begin();x!=items.end() && found;++x) {
        found = x->isDone();
    }
    return found;

}

Time ToDoList::getDuration() {
    return Time();
}

void ToDoList::serialize() {

}
