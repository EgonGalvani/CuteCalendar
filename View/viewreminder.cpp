#include <stdexcept>

#include "viewreminder.h"
#include "Model/Hierarchy/reminder.h"

ViewPromemoria::ViewPromemoria(QWidget *parent) : ModView(parent) {

    inizio= new QTimeEdit();
    fine= new QTimeEdit();
    alert = new QTimeEdit(this);
    checkRep= new QCheckBox();

    start = new QLabel("Inizio");
    end = new QLabel("Fine");
    alertL= new QLabel("Alert");
    rep = new QLabel("Ripeti");

    mainLayout->addWidget(start);
    mainLayout->addWidget(inizio);
    mainLayout->addWidget(end);
    mainLayout->addWidget(fine);
    mainLayout->addWidget(alertL);
    mainLayout->addWidget(alert);
    mainLayout->addWidget(rep);
    mainLayout->addWidget(checkRep);

}

void ViewPromemoria::setEnabled(bool e) {
    ModView::setEnabled(e);
    inizio->setEnabled(e);
    fine->setEnabled(e);
    alert->setEnabled(e);
    checkRep->setEnabled(e);
}

void ViewPromemoria::pushSaves(Model::It it) {
    ModView::pushSaves(it);

    Reminder* currEve = dynamic_cast<Reminder*>(&**it);
    if(currEve) {
        currEve->setStartTime(inizio->time());
        currEve->setEndTime(fine->time());
        currEve->setAlertTime(alert->time());
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
        alert->setTime(currEve->getAlertTime());
        checkRep->setChecked(currEve->doesRepeat());
    } else {
        throw std::logic_error("Tipo errato per essere mostrato come reminder");
    }
}

Reminder *ViewPromemoria::createEvent()
{
    Reminder* ritorno = new Reminder(10,inizio->time(),fine->time(),alert->time(),checkRep->isChecked(),txtNome->text().toStdString(),txtDesc->toPlainText().toStdString(),txtLuogo->text().toStdString(),Date(12,12,2000),checkTag->getTags());
    return ritorno;
}
