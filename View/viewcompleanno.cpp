#include "viewcompleanno.h"

ViewCompleanno::ViewCompleanno(QWidget *parent)
    : ModView(parent) {

    nascita = new QLabel("Anno di Nascita");
    annoNascita = new QSpinBox(this);
    annoNascita->setRange(1900,2100);
    annoNascita->setReadOnly(true);
    mainLayout->addWidget(nascita);
    mainLayout->addWidget(annoNascita);


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
     BirthDay* currEve = dynamic_cast< BirthDay*>(&**it);
    if(currEve) {
        annoNascita->setValue(currEve->getNascita());
    } else
        throw std::logic_error("Tipo errato per essere mostrato come allenamento");
}




