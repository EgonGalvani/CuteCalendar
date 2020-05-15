#include "viewpromemoria.h"



void ViewPromemoria::modifyPushed()
{
    ModView::modifyPushed();
    inizio->setEnabled(true);
    fine->setEnabled(true);
    checkRep->setEnabled(true);


}

void ViewPromemoria::confirmPushed()
{

}

void ViewPromemoria::deletePushed()
{

}

ViewPromemoria::ViewPromemoria(QDialog *parent) : ModView(parent)
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

    editLayout->addWidget(start);
    editLayout->addWidget(inizio);
    editLayout->addWidget(end);
    editLayout->addWidget(fine);
    editLayout->addWidget(rep);
    editLayout->addWidget(checkRep);



    setLayout(mainLayout);

}

ViewPromemoria::~ViewPromemoria() {

}

void ViewPromemoria::getInfo()
{

}
