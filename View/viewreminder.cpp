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

    inizio->setTime(QTime::currentTime());
    if(inizio->time().hour()<23)
        fine->setTime(inizio->time().addSecs(3600));
    else fine->setTime(QTime::fromString("23:59:00"));


    start = new QLabel("Inizio",this);
    end = new QLabel("Fine",this);
    alertL= new QLabel("Notifica",this);
    rep = new QLabel("Ripeti",this);
    urg= new QLabel("Urgenza",this);

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
//Passaggio del contenuto della view al Model per il salvataggio delle modifiche.
void ViewPromemoria::pushSaves(Model::It it,QString& err) {
    ModView::pushSaves(it,err);

    Reminder* currEve = dynamic_cast<Reminder*>(&**it);
    if(currEve) {
        if (checkPushable(err)){
            currEve->setStartTime(inizio->time());
            currEve->setEndTime(fine->time());
            currEve->setUrgency(urgency->value());


            QTime* currInizio = new QTime(inizio->time());

            QTime t2 =currInizio->addSecs(alert->value()*(-60));

            currEve->setAlertTime(t2);
            currEve->setRepeat(checkRep->isChecked());

            delete currInizio;
        }else {

            throw std::logic_error("Errore nella modifica");
        }

     } else
        throw std::logic_error("Tipo errato per apportare le modifiche del reminder");
}

//Caricamento del contenuto delle evento nella view
void ViewPromemoria::fillView(const Model::It& it) {
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

//Controllo errori nella view prima del salvataggio
bool ViewPromemoria::checkPushable(QString& err) {
    bool ritorno=ModView::checkPushable(err);
    if(!inizio->time().isValid()){
        ritorno=false;
        err+="Il campo Inizio non è valido.\n";

    }
    if(!fine->time().isValid()){
        ritorno=false;
        err+="Il campo Fine non è valido.\n" ;
    }
    if(!(inizio->time() < fine->time())){
        ritorno=false;
        err+="Il campo Inizio deve essere minore di Fine.\n";
    }

    if(alert->value()<5){
        ritorno=false;
       err+="Il minimo valore per il campo Alert accettato è 5.\n";
    }

    return   ritorno;
}

/**Funzione che crea un evento Reminder e lo ritorna
@param date: data nella quale viene creato l'evento
**/
Reminder *ViewPromemoria::createEvent(QDate date,QString& err)
{
    if(checkPushable(err)){

        QTime* currInizio = new QTime(inizio->time());
        QTime t2 =currInizio->addSecs(alert->value()*-60);
        Reminder* ritorno = new Reminder(urgency->value(),inizio->time(),fine->time(),t2,checkRep->isChecked(),txtNome->text().toStdString(),txtDesc->toPlainText().toStdString(),txtLuogo->text().toStdString(),Date(date),checkTag->getTags());
        delete currInizio;
        return ritorno;
    }else throw std::logic_error("Errore nella creazione");
}
