#include "todolist.h"

//METODI LIST ITEM

//std::vector<ListItem> items;

ToDoList::ListItem::ListItem(const std::string& x, bool y) : _description(x),_done(y) {}

std::string ToDoList::ListItem::getDescription() const {
    return _description;
}

bool ToDoList::ListItem::isDone() const {
    return _done;
}

void ToDoList::ListItem::setDone(const bool x) {
    _done = x;
}

void ToDoList::ListItem::serialize(QJsonObject &json) const {

    json["item_description"] = QString::fromStdString(_description);
    json["item_isdone"] = isDone();

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

    AllDayEvent::serialize(json);
    json.insert("ID",ToDoList::ID);
    //Rappresenterà tutta la todolist,verrà inserito come campo dentro il json originale
    //es {"TODOLIST" : { [ {ciao,0},{addio,1}, ...}
    QJsonObject listjson;
    QJsonArray arrayToDo = QJsonArray();
    for (auto it = items.begin();it!=items.end();++it) {
        QJsonObject itemjson = QJsonObject();
        //serializza ogni item
        (*it).serialize(itemjson);
        arrayToDo.push_back(itemjson);
    }
    json["TODOLIST"] = arrayToDo;

}

void ToDoList::clear() {
    items.clear();
}

void ToDoList::addItem(const std::string & x, bool y) {
    items.push_back(ListItem(x,y));
}

void ToDoList::addItems(std::vector<std::pair<std::string, bool> > *vecItems) {
    for (std::vector<std::pair<std::string,bool>>::const_iterator it = vecItems->begin();
         it!=vecItems->end();++it) {
        items.push_back(ListItem((*it).first,(*it).second));

    }
}

ToDoList::ToDoList(const std::string& nome,const std::string& descr,
                   const std::string& luogo,
                   const Date& dataEvento,const std::vector<std::string>& vettoreTag,
                   std::vector<std::pair<std::string,bool>>* vecItems)
    :Event(nome,descr,luogo,dataEvento,vettoreTag),
    AllDayEvent () {
    items = std::vector<ToDoList::ListItem>();
    if (vecItems!=nullptr) {
        addItems(vecItems);
    }
}

