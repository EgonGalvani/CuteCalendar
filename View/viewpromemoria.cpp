#include <stdexcept>

#include "viewpromemoria.h"
#include "Model/Hierarchy/reminder.h"

ViewPromemoria::ViewPromemoria(QWidget *parent) : ModView(parent) {

    inizio= new QTimeEdit();
    fine= new QTimeEdit();
    checkRep= new QCheckBox();

    start = new QLabel("Inizio");
    end = new QLabel("Fine");
    rep = new QLabel("Ripeti");

    mainLayout->addWidget(start);
    mainLayout->addWidget(inizio);
    mainLayout->addWidget(end);
    mainLayout->addWidget(fine);
    mainLayout->addWidget(rep);
    mainLayout->addWidget(checkRep);
}

void ViewPromemoria::setEnabled(bool e) {
    ModView::setEnabled(e);
    inizio->setEnabled(e);
    fine->setEnabled(e);
    checkRep->setEnabled(e);
}

void ViewPromemoria::pushSaves(Model::It it) {
    ModView::pushSaves(it);

    Reminder* currEve = dynamic_cast<Reminder*>(&**it);
    if(currEve) {
        currEve->setStartTime(inizio->time());
        currEve->setEndTime(fine->time());
        currEve->setRepeat(checkRep->isChecked());
     } else
        throw std::logic_error("Tipo errato per apportare le modifiche del reminder");
}

void ViewPromemoria::fillView(Model::It it) {
    ModView::fillView(it);

    Reminder* currEve = dynamic_cast<Reminder*>(&**it);
    if(currEve) {
        inizio->setTime(currEve->getStartTime());
        fine->setTime(currEve->getEndTime());
        checkRep->setChecked(currEve->doesRepeat());
    } else {
        throw std::logic_error("Tipo errato per essere mostrato come reminder");
    }
}
