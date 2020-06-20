#include "viewbirthday.h"


ViewBirthday::ViewBirthday(QWidget *parent)
    : ModView(parent) {
    //init grafica
    nascita = new QLabel("Anno di Nascita");
    annoNascita = new QSpinBox(this);

    annoNascita->setRange(1900,2100);

    mainLayout->addWidget(nascita);
    mainLayout->addWidget(annoNascita);
}

/**Funzione che crea un evento Birthday e lo ritorna
@param date: data nella quale viene creato l'evento
**/
BirthDay *ViewBirthday::createEvent(const QDate& date)
{
    QString error = "";
    if(checkPushable(error)){ //controllo che l'evento da inserire sia corretto
        return new BirthDay(annoNascita->text().toUShort(),txtNome->text().toStdString(),txtDesc->toPlainText().toStdString(),txtLuogo->text().toStdString(), Date(date), checkTag->getTags());
    }else
        throw std::logic_error(error.toStdString());
}

//Set delle componenti della view a enabled se e==TRUE o disabled se e==FALSE
void ViewBirthday::setEnabled(bool e) {
    ModView::setEnabled(e);
    annoNascita->setReadOnly(!e);
}

// Salvataggio delle modifiche apportate dall'utente nell'iteratore passato
void ViewBirthday::pushSaves(const Model::It& it) const {
    ModView::pushSaves(it);

    BirthDay* currEve = dynamic_cast<BirthDay*>(&**it);
    if(currEve) {
        QString error = "";
        if(checkPushable(error)){
            currEve->setNascita(annoNascita->value());
        }else{
            throw std::logic_error(error.toStdString());
        }
    } else
        throw std::logic_error("Tipo errato per la modifica di un Compleanno");
}

//Controllo errori nella view prima del salvataggio
bool ViewBirthday::checkPushable(QString& err) const {

    bool ritorno = ModView::checkPushable(err);
    if(annoNascita->value() > QDate::currentDate().year()) {
        ritorno = false;
        err += "L'anno di nascita non può essere maggiore di quello corrente.\n";
    }

    return ritorno;
}

// Caricamento del contenuto delle evento nella view
void ViewBirthday::fillView(const Model::It& it) {
    ModView::fillView(it);

    BirthDay* currEve = dynamic_cast< BirthDay*>(&**it);
    if(currEve) {
        annoNascita->setValue(currEve->getNascita());
    } else
        throw std::logic_error("Tipo errato per essere mostrato come Compleanno");
}




