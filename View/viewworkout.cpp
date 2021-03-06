#include <stdexcept>

#include "viewworkout.h"
#include "Model/Hierarchy/workout.h"

ViewWorkout::ViewWorkout(QWidget *parent)
        : ModView(parent) {

    inizio= new QTimeEdit(this);
    fine= new QTimeEdit(this);
    start = new QLabel("Inizio",this);
    end = new QLabel("Fine",this);
    attivita = new QComboBox(this);

    attivita->addItem("Calcio");
    attivita->addItem("Pallavolo");
    attivita->addItem("Nuoto");
    attivita->addItem("Piscina");
    attivita->addItem("Palestra");

    // vengono impostati i valori di default
    inizio->setTime(QTime::currentTime());
    if(inizio->time().hour()<23)
        fine->setTime(inizio->time().addSecs(3600));
    else fine->setTime(QTime::fromString("23:59:00"));

    mainLayout->addWidget(attivita);
    mainLayout->addWidget(start);
    mainLayout->addWidget(inizio);
    mainLayout->addWidget(end);
    mainLayout->addWidget(fine);
}

void ViewWorkout::setEnabled(bool e) {
    ModView::setEnabled(e);
    inizio->setEnabled(e);
    fine->setEnabled(e);
    attivita->setEnabled(e);
}

// Salvataggio delle modifiche apportate dall'utente nell'iteratore passato
void ViewWorkout::pushSaves(const Model::It& it) const {
    ModView::pushSaves(it);

    Workout* currEve = dynamic_cast<Workout*>(&**it);
    if(currEve) {
        QString error = "";
        if(checkPushable(error)){
            currEve->setStartTime(inizio->time());
            currEve->setEndTime(fine->time());
            currEve->setActivity(attivita->currentIndex()+1);
        } else
            throw std::logic_error(error.toStdString());
    } else
        throw std::logic_error("Tipo errato per la modifica di un allenamento");
}

//Caricamento del contenuto delle evento nella view
void ViewWorkout::fillView(const Model::It& it) {

    ModView::fillView(it);

    Workout* currEve = dynamic_cast<Workout*>(&**it);
    if(currEve) {
        inizio->setTime(currEve->getStartTime());
        fine->setTime(currEve->getEndTime());
        attivita->setCurrentIndex(currEve->getActivity()-1);
    } else
        throw std::logic_error("Tipo errato per essere mostrato come allenamento");
}

//Controllo errori nella view prima del salvataggio
bool ViewWorkout::checkPushable(QString& err) const {

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

    if(attivita->currentText().trimmed().isEmpty()){
        ritorno=false;
        err+="Il campo attività non può essere vuoto.\n";
    }

    return ritorno;
}

/**Funzione che crea un evento Workout e lo ritorna
@param date: data nella quale viene creato l'evento
**/
Workout* ViewWorkout::createEvent(const QDate& date) const {
    QString error = "";
    if(checkPushable(error)){
        return new Workout(attivita->currentIndex()+1,inizio->time(),fine->time(),txtNome->text().toStdString(),txtDesc->toPlainText().toStdString(),txtLuogo->text().toStdString(),Date(date),checkTag->getTags());
    } else throw std::logic_error(error.toStdString());
}


