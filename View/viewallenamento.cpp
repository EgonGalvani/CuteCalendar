#include "viewallenamento.h"
#include "Model/Hierarchy/workout.h"



ViewAllenamento::ViewAllenamento(QWidget *parent) : ModView(parent) {

    inizio= new QTimeEdit();
    fine= new QTimeEdit();
    start = new QLabel("Inizio");
    end = new QLabel("Fine");

    inizio->setEnabled(false);
    fine->setEnabled(false);

    mainLayout->addWidget(start);
    mainLayout->addWidget(inizio);
    mainLayout->addWidget(end);
    mainLayout->addWidget(fine);




}

ViewAllenamento::~ViewAllenamento() {


}

void ViewAllenamento::switchReadable()
{
    ModView::switchReadable();
    inizio->setEnabled(true);
    fine->setEnabled(true);

}


