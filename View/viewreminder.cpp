#include <stdexcept>

#include "viewreminder.h"
#include "Model/Hierarchy/reminder.h"

ViewPromemoria::ViewPromemoria(QWidget *parent) : ModView(parent) {

    inizio= new QTimeEdit(this);
    fine= new QTimeEdit(this);
    alert = new QSpinBox(this);
    checkRep= new QCheckBox(this);
    urgency = new QSpinBox(this);

    urgency->setRange(1,10);
    alert->setRange(5,60);
    alert->setSingleStep(5);


    start = new QLabel("Inizio");
    end = new QLabel("Fine");
    alertL= new QLabel("Alert");
    rep = new QLabel("Ripeti");
    urg= new QLabel("Urgency");

    mainLayout->addWidget(start);
    mainLayout->addWidget(inizio);
    mainLayout->addWidget(end);
    mainLayout->addWidget(fine);
    mainLayout->addWidget(alertL);
    mainLayout->addWidget(alert);
    mainLayout->addWidget(rep);
    mainLayout->addWidget(checkRep);
    mainLayout->addWidget(urg);
    mainLayout->addWidget(urgency);

}

void ViewPromemoria::setEnabled(bool e) {
    ModView::setEnabled(e);
    inizio->setEnabled(e);
    fine->setEnabled(e);
    alert->setEnabled(e);
    checkRep->setEnabled(e);
    urgency->setReadOnly(!e);

}

void ViewPromemoria::pushSaves(Model::It it) {
    ModView::pushSaves(it);

    Reminder* currEve = dynamic_cast<Reminder*>(&**it);
    if(currEve) {
        currEve->setStartTime(inizio->time());
        currEve->setEndTime(fine->time());
        //currEve->setUrgency(urgency->text());


        QTime* currInizio = new QTime(inizio->time());

        QTime t2 =currInizio->addSecs(alert->value()*(-60));

        currEve->setAlertTime(t2);
        currEve->setRepeat(checkRep->isChecked());

        delete currInizio;


     } else
        throw std::logic_error("Tipo errato per apportare le modifiche del reminder");
}

void ViewPromemoria::fillView(Model::It it) {
    ModView::fillView(it);

    Reminder* currEve = dynamic_cast<Reminder*>(&**it);
    if(currEve) {
        inizio->setTime(currEve->getStartTime());
        fine->setTime(currEve->getEndTime());
        urgency->setValue(currEve->getUrgency());

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
    QTime t2 =currInizio->addSecs(alert->value()*-60);


    Reminder* ritorno = new Reminder(urgency->value(),inizio->time(),fine->time(),t2,checkRep->isChecked(),txtNome->text().toStdString(),txtDesc->toPlainText().toStdString(),txtLuogo->text().toStdString(),Date(date),checkTag->getTags());
    delete currInizio;
    return ritorno;
}
