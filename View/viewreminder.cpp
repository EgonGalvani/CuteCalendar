#include <stdexcept>

#include "viewreminder.h"
#include "Model/Hierarchy/reminder.h"

ViewPromemoria::ViewPromemoria(QWidget *parent) : ModView(parent) {

    inizio= new QTimeEdit(this);
    fine= new QTimeEdit(this);
    alert = new QSpinBox(this);
    checkRep= new QCheckBox(this);

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


        QTime* currInizio = new QTime(inizio->time());

        QTime t2 =currInizio->addSecs(alert->value()*(-60));

        currEve->setAlertTime(t2);
        currEve->setRepeat(checkRep->isChecked());

        delete currInizio;

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

        QTime* currInizio = new QTime(inizio->time());
        QTime* currAlert = new QTime(currEve->getAlertTime());
        int secs = currInizio->secsTo(*currAlert);



        alert->setValue(secs/-60);

        delete currInizio;
        delete currAlert;

        checkRep->setChecked(currEve->doesRepeat());
    } else {
        throw std::logic_error("Tipo errato per essere mostrato come reminder");
    }
}

Reminder *ViewPromemoria::createEvent(QDate date)
{
    QTime* currInizio = new QTime(inizio->time());
    currInizio->addSecs(alert->value()*-60);

    Reminder* ritorno = new Reminder(10,inizio->time(),fine->time(),*currInizio,checkRep->isChecked(),txtNome->text().toStdString(),txtDesc->toPlainText().toStdString(),txtLuogo->text().toStdString(),Date(date),checkTag->getTags());
    delete currInizio;
    return ritorno;
}
