#include <stdexcept>

#include "viewworkout.h"
#include "Model/Hierarchy/workout.h"

ViewAllenamento::ViewAllenamento(QWidget *parent)
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

void ViewAllenamento::setEnabled(bool e) {
    ModView::setEnabled(e);
    inizio->setEnabled(e);
    fine->setEnabled(e);
    attivita->setEnabled(e);

}
//Passaggio del contenuto della view al Model per il salvataggio delle modifiche.
void ViewAllenamento::pushSaves(Model::It it) {
    ModView::pushSaves(it);

    Workout* currEve = dynamic_cast<Workout*>(&**it);
    if(currEve) {
        if(checkPushable()){
            currEve->setStartTime(inizio->time());
            currEve->setEndTime(fine->time());
            currEve->setActivity(attivita->currentIndex()+1);
        } else {

            throw std::logic_error("Errore nella modifica");}
    } else
        throw std::logic_error("Tipo errato per la modifica di un allenamento");
}
//Caricamento del contenuto delle evento nella view
void ViewAllenamento::fillView(Model::It it) {
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
bool ViewAllenamento::checkPushable(){

    bool ritorno=ModView::checkPushable();
    if(!inizio->time().isValid()){
        ritorno=false;
        ModView::errori+="Il campo Inizio non è valido. ";

    }
    if(!fine->time().isValid()){
        ritorno=false;
        ModView::errori+="Il campo Fine non è valido. " ;
    }
    if(!(inizio->time() < fine->time())){
        ritorno=false;
        ModView::errori+="Il campo Inizio deve essere minore di Fine. ";
    }

    if(attivita->currentText().isEmpty()){
        ritorno=false;
        ModView::errori+="Il campo attività non può essere vuoto. ";
    }

    return   ritorno;
}
/**Funzione che crea un evento Workout e lo ritorna
@param date: data nella quale viene creato l'evento
**/
Workout *ViewAllenamento::createEvent(QDate date)
{

    if(checkPushable()){
        Workout* ritorno = new Workout(attivita->currentIndex()+1,inizio->time(),fine->time(),txtNome->text().toStdString(),txtDesc->toPlainText().toStdString(),txtLuogo->text().toStdString(),Date(date),checkTag->getTags());
        return ritorno;
    } else throw std::logic_error("Errore nella creazione");

}


