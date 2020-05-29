#include "viewbirthday.h"

ViewCompleanno::ViewCompleanno(QWidget *parent)
    : ModView(parent) {

    nascita = new QLabel("Anno di Nascita");
    annoNascita = new QSpinBox(this);

    annoNascita->setRange(1900,2100);

    mainLayout->addWidget(nascita);
    mainLayout->addWidget(annoNascita);


}

BirthDay *ViewCompleanno::createEvent(QDate date)
{
    if(checkPushable()){
        BirthDay* ritorno = new BirthDay(annoNascita->text().toUShort(),txtNome->text().toStdString(),txtDesc->toPlainText().toStdString(),txtLuogo->text().toStdString(), Date(date), checkTag->getTags());
        return ritorno;
    }else throw std::logic_error("Fratellì sto inserimento non si fa se non mi controlli bene i campi");
}

void ViewCompleanno::setEnabled(bool e)
{
    ModView::setEnabled(e);
    annoNascita->setReadOnly(!e);

}

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

void ViewCompleanno::fillView(Model::It it)
{
    ModView::fillView(it);
     BirthDay* currEve = dynamic_cast< BirthDay*>(&**it);
    if(currEve) {
        annoNascita->setValue(currEve->getNascita());
    } else
        throw std::logic_error("Tipo errato per essere mostrato come Compleanno");
}

bool ViewCompleanno::checkPushable()
{
    return ModView::checkPushable() && !annoNascita->text().isEmpty();
}




