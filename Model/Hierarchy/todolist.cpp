#include "todolist.h"

//METODI LIST ITEM

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



//Virtual methods
//Controlla ogni elemento del vettore se è done;
bool ToDoList::isCompleted() {
    return false;
}

void ToDoList::serialize() {

}
