#include "viewtodolist.h"
#include "../Model/Hierarchy/todolist.h"

#include <QMessageBox>
#include <QLabel>

ViewToDoList::ViewToDoList(QWidget* parent)
    : ModView(parent), checkList(new CheckList(this)),
      inputLine(new EnterLineEdit(this)){

    inputLine->setPlaceholderText("Inserisci testo del task e premi invio");
    connect(inputLine, SIGNAL(enterKeyPressed()), this, SLOT(addItem()));

    mainLayout->addWidget(new QLabel("Task", this));
    mainLayout->addWidget(inputLine);
    mainLayout->addWidget(checkList);
}

void ViewToDoList::setEnabled(bool b) {
    ModView::setEnabled(b);
    checkList->setEnabled(b);
    inputLine->setEnabled(b);
}

void ViewToDoList::pushSaves(const Model::It& it) const {
    ModView::pushSaves(it);

    ToDoList* currEve = dynamic_cast<ToDoList*>(&**it);
    if(currEve) {
        QString error = "";
        if(checkPushable(error)){
            currEve->clear();
            for(auto item : checkList->getStatus())
                currEve->addItem(item.first, item.second);
        } else
            throw std::logic_error(error.toStdString());
    } else
        throw std::logic_error("Tipo errato per salvataggio da view todolist");
}

void ViewToDoList::fillView(const Model::It& it) {
    ModView::fillView(it);

    ToDoList* currEve = dynamic_cast<ToDoList*>(&**it);
    if(currEve) {
        for(auto item : currEve->getItems())
            checkList->addItem(QString::fromStdString(item.getDescription()), item.isDone());
    } else
        throw std::logic_error("Tipo errato per essere mostrato in una view todolist");
}

bool ViewToDoList::checkPushable(QString& err) const {
    bool ritorno= ModView::checkPushable(err);

    if(checkList->getStatus().size()==0){
        ritorno=false;
        err+="La ToDoList non può essere vuota.\n";
    }

    return ritorno;
}

void ViewToDoList::addItem() {
    try {
        checkList->addItem(inputLine->text());
    } catch(std::exception& e) {
        QMessageBox::critical(this, QString("Error"), QString::fromStdString(e.what()));
    }

    inputLine->clear();
}

ToDoList* ViewToDoList::createEvent(const QDate& date) const {
    QString error = "";
    if(checkPushable(error)){
        ToDoList* ritorno = new ToDoList(txtNome->text().toStdString(),txtDesc->toPlainText().toStdString(),txtLuogo->text().toStdString(), Date(date), checkTag->getTags());
        for(auto item : checkList->getStatus())
            ritorno->addItem(item.first, item.second);
        return ritorno;
    }else throw std::logic_error(error.toStdString());
}
