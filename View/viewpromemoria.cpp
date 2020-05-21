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






}

ViewPromemoria::~ViewPromemoria() {

}

void ViewPromemoria::switchReadable()
{
    ModView::switchReadable();
    inizio->setEnabled(true);
    fine->setEnabled(true);
    checkRep->setEnabled(true);

}

void ViewPromemoria::pushSaves(Model::It it)
{
    ModView::pushSaves(it);

    Reminder* currEve = dynamic_cast<Reminder*>(&**it);

    currEve->setStartTime(inizio->time());
    currEve->setEndTime(fine->time());
    currEve->setRepeat(checkRep->isChecked());

}

void ViewPromemoria::fillView(Model::It it)
{
    ModView::fillView(it);

    Reminder* currEve = dynamic_cast<Reminder*>(&**it);

    inizio->setTime(currEve->getStartTime());
    fine->setTime(currEve->getEndTime());
    checkRep->setChecked(currEve->doesRepeat());


}
