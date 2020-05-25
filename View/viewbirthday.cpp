#include "viewbirthday.h"

ViewCompleanno::ViewCompleanno(QDate date,QWidget *parent)
    : ModView(date,parent) {

    nascita = new QLabel("Anno di Nascita");
    annoNascita = new QSpinBox(this);

    annoNascita->setRange(1900,2100);

    mainLayout->addWidget(nascita);
    mainLayout->addWidget(annoNascita);


}

BirthDay *ViewCompleanno::createEvent()
{
    //CHieder a egon la conversione da QDate a Date domani <3
    BirthDay* ritorno = new BirthDay(annoNascita->text().toUShort(),txtNome->text().toStdString(),txtDesc->toPlainText().toStdString(),txtLuogo->text().toStdString(), Date(12, 5, 2020), checkTag->getTags());
    return ritorno;
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
        //currEve->setNascita(annoNascita->value());
    } else
        throw std::logic_error("Tipo errato per la modifica di un allenamento");

}

void ViewCompleanno::fillView(Model::It it)
{
    ModView::fillView(it);
     BirthDay* currEve = dynamic_cast< BirthDay*>(&**it);
    if(currEve) {
        annoNascita->setValue(currEve->getNascita());
    } else
        throw std::logic_error("Tipo errato per essere mostrato come allenamento");
}




