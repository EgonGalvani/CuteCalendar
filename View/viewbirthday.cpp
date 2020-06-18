#include "viewbirthday.h"


ViewCompleanno::ViewCompleanno(QWidget *parent)
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
BirthDay *ViewCompleanno::createEvent(QDate date)
{
    if(checkPushable()){ //controllo che l'evento da inserire sia corretto
        BirthDay* ritorno = new BirthDay(annoNascita->text().toUShort(),txtNome->text().toStdString(),txtDesc->toPlainText().toStdString(),txtLuogo->text().toStdString(), Date(date), checkTag->getTags());
        return ritorno;
    }else throw std::logic_error("Fratellì sto inserimento non si fa se non mi controlli bene i campi");
}

//Set delle componenti della view a enabled se e==TRUE o disabled se e==FALSE
void ViewCompleanno::setEnabled(bool e)
{
    ModView::setEnabled(e);
    annoNascita->setReadOnly(!e);

}

//Passaggio del contenuto della view al Model per il salvataggio delle modifiche.
void ViewCompleanno::pushSaves(Model::It it)
{
    ModView::pushSaves(it);

    BirthDay* currEve = dynamic_cast<BirthDay*>(&**it);
    if(currEve) {
        if(checkPushable()){
            currEve->setNascita(annoNascita->value());
        }else{
            QMessageBox::critical(this, QString("Error"), "Qualche campo vuoto non ho tempo di fare tutti i vari check quindi arrangiati fratellì");
            throw std::logic_error("Fratellì sto inserimento non si fa se non mi controlli bene i campi");
        }
    } else
        throw std::logic_error("Tipo errato per la modifica di un Compleanno");

}
//Caricamento del contenuto delle evento nella view
void ViewCompleanno::fillView(Model::It it)
{
    ModView::fillView(it);
     BirthDay* currEve = dynamic_cast< BirthDay*>(&**it);
    if(currEve) {
        annoNascita->setValue(currEve->getNascita());
    } else
        throw std::logic_error("Tipo errato per essere mostrato come Compleanno");
}
//Controllo errori nella view prima del salvataggio
bool ViewCompleanno::checkPushable()
{
    return ModView::checkPushable() && !annoNascita->text().isEmpty();
}




