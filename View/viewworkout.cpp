#include <stdexcept>

#include "viewworkout.h"
#include "Model/Hierarchy/workout.h"

ViewAllenamento::ViewAllenamento(QDate date,QWidget *parent)
        : ModView(date,parent) {

    inizio= new QTimeEdit();
    fine= new QTimeEdit();
    start = new QLabel("Inizio");
    end = new QLabel("Fine");

    mainLayout->addWidget(start);
    mainLayout->addWidget(inizio);
    mainLayout->addWidget(end);
    mainLayout->addWidget(fine);
}

void ViewAllenamento::setEnabled(bool e) {
    ModView::setEnabled(e);
    inizio->setEnabled(e);
    fine->setEnabled(e);
}

void ViewAllenamento::pushSaves(Model::It it) {
    ModView::pushSaves(it);

    Workout* currEve = dynamic_cast<Workout*>(&**it);
    if(currEve) {
        currEve->setStartTime(inizio->time());
        currEve->setEndTime(fine->time());
    } else
        throw std::logic_error("Tipo errato per la modifica di un allenamento");
}

void ViewAllenamento::fillView(Model::It it) {
    ModView::fillView(it);

    Workout* currEve = dynamic_cast<Workout*>(&**it);
    if(currEve) {
        inizio->setTime(currEve->getStartTime());
        fine->setTime(currEve->getEndTime());
    } else
        throw std::logic_error("Tipo errato per essere mostrato come allenamento");
}

Workout *ViewAllenamento::createEvent()
{
    //manca attivita data etc
    Workout* ritorno = new Workout(12,inizio->time(),fine->time(),txtNome->text().toStdString(),txtDesc->toPlainText().toStdString(),txtLuogo->text().toStdString(),Date(12,12,2000),checkTag->getTags());
    return ritorno;
}


