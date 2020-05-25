#include "todolist.h"

//METODI LIST ITEM

//std::vector<ListItem> items;

ToDoList::ListItem::ListItem(const std::string& x, bool y) : description(x),done(y) {}

std::string ToDoList::ListItem::getDescription() const {
    return description;
}

bool ToDoList::ListItem::isDone() const {
    return done;
}

void ToDoList::ListItem::setDone(const bool x) {
    done = x;
}

//std::vector<ListItem*> getItems;
std::vector<ToDoList::ListItem> ToDoList::getItems() const  {
    return items;
}

ToDoList* ToDoList::clone() const {
    return new ToDoList(*this);
}

//Virtual methods
//Controlla ogni elemento del vettore se è done;
bool ToDoList::isCompleted() const {
    bool found = true;
    for (std::vector<ListItem>::const_iterator x= items.begin();
         x!=items.end() && found;++x) {

        found = x->isDone();
    }

    return found;
}

Time ToDoList::getDuration() const {
    return Time();
}

void ToDoList::serialize(QJsonObject &json) const {

}
