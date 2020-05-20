#include "viewpromemoria.h"
#include "Model/Hierarchy/reminder.h"




ViewPromemoria::ViewPromemoria(QWidget *parent) : ModView(parent)
{
    inizio= new QTimeEdit();
    fine= new QTimeEdit();

    checkRep= new QCheckBox();

    start = new QLabel("Inizio");
    end = new QLabel("Fine");
    rep = new QLabel("Ripeti");


    inizio->setEnabled(false);
    fine->setEnabled(false);
    checkRep->setEnabled(false);

    mainLayout->addWidget(start);
    mainLayout->addWidget(inizio);
    mainLayout->addWidget(end);
    mainLayout->addWidget(fine);
    mainLayout->addWidget(rep);
    mainLayout->addWidget(checkRep);




    setLayout(mainLayout);

}

ViewPromemoria::~ViewPromemoria() {

}


