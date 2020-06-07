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
    else fine->setTime(QTime::fromString("23:59:99"));



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

void ViewAllenamento::pushSaves(Model::It it) {
    ModView::pushSaves(it);

    Workout* currEve = dynamic_cast<Workout*>(&**it);
    if(currEve) {
        if(checkPushable()){
            currEve->setStartTime(inizio->time());
            currEve->setEndTime(fine->time());
            currEve->setActivity(attivita->currentIndex()+1);
        } else {
            QMessageBox::critical(this, QString("Error"), "Qualche campo vuoto non ho tempo di fare tutti i vari check quindi arrangiati fratellì");
            throw std::logic_error("Fratellì sto inserimento non si fa se non mi controlli bene i campi");}
    } else
        throw std::logic_error("Tipo errato per la modifica di un allenamento");
}

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

bool ViewAllenamento::checkPushable(){

    return ModView::checkPushable() && inizio->time().isValid() && fine->time().isValid() && (inizio->time() < fine->time()) && !attivita->currentText().isEmpty();
}

Workout *ViewAllenamento::createEvent(QDate date)
{

    if(checkPushable()){
        Workout* ritorno = new Workout(attivita->currentIndex()+1,inizio->time(),fine->time(),txtNome->text().toStdString(),txtDesc->toPlainText().toStdString(),txtLuogo->text().toStdString(),Date(date),checkTag->getTags());
        return ritorno;
    } else throw std::logic_error("Fratellì sto inserimento non si fa se non mi controlli bene i campi");

}


