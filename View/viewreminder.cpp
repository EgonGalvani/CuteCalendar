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
    alertL= new QLabel("Notifica");
    rep = new QLabel("Ripeti");
    urg= new QLabel("Urgenza");

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
        if (checkPushable()){
            currEve->setStartTime(inizio->time());
            currEve->setEndTime(fine->time());
            currEve->setUrgency(urgency->value());


            QTime* currInizio = new QTime(inizio->time());

            QTime t2 =currInizio->addSecs(alert->value()*(-60));

            currEve->setAlertTime(t2);
            currEve->setRepeat(checkRep->isChecked());

            delete currInizio;
        }else {
            QMessageBox::critical(this, QString("Error"), "Qualche campo vuoto non ho tempo di fare tutti i vari check quindi arrangiati fratellì");
            throw std::logic_error("Fratellì sto inserimento non si fa se non mi controlli bene i campi");
        }

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

bool ViewPromemoria::checkPushable()
{
    return ModView::checkPushable() && inizio->time().isValid() && fine->time().isValid() && (inizio->time() < fine->time()) && alert->value()%5==0 ;
}

Reminder *ViewPromemoria::createEvent(QDate date)
{
    if(checkPushable()){

        QTime* currInizio = new QTime(inizio->time());
        QTime t2 =currInizio->addSecs(alert->value()*-60);
        Reminder* ritorno = new Reminder(urgency->value(),inizio->time(),fine->time(),t2,checkRep->isChecked(),txtNome->text().toStdString(),txtDesc->toPlainText().toStdString(),txtLuogo->text().toStdString(),Date(date),checkTag->getTags());
        delete currInizio;
        return ritorno;
    }else throw std::logic_error("Fratellì sto inserimento non si fa se non mi controlli bene i campi");
}
