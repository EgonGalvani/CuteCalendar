#include "viewallenamento.h"
#include "Model/Hierarchy/workout.h"


void ViewAllenamento::modifyPushed()
{
    ModView::modifyPushed();
    inizio->setEnabled(true);
    fine->setEnabled(true);
}

void ViewAllenamento::confirmPushed()
{

}



ViewAllenamento::ViewAllenamento(const Model::It& it,QDialog *parent) : ModView(it,parent) {

    inizio= new QTimeEdit();
    fine= new QTimeEdit();
    start = new QLabel("Inizio");
    end = new QLabel("Fine");

    inizio->setEnabled(false);
    fine->setEnabled(false);

    editLayout->addWidget(start);
    editLayout->addWidget(inizio);
    editLayout->addWidget(end);
    editLayout->addWidget(fine);

    getInfo();

    setLayout(mainLayout);
}

ViewAllenamento::~ViewAllenamento() {

}

void ViewAllenamento::getInfo()
{
    ModView::getInfo();
    Workout* currEve = dynamic_cast<Workout*>(&**it);
    //inizio->setTime(currEve->getStartTime());
   // fine->setTime(currEve->getEndTime());
}


