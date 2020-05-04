#include "newevent.h"


NewEvent::NewEvent(QWidget *parent) :
    QWidget(parent) {

    QLabel * prova=new QLabel(tr("Provone"));
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(prova);
    setLayout(layout);
}

NewEvent::~NewEvent() {

}
