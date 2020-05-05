#include "newevent.h"


NewEvent::NewEvent(QDialog *parent) :
    QDialog(parent) {

    QLabel * prova=new QLabel(tr("Provone"));
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(prova);
    setLayout(layout);
}

NewEvent::~NewEvent() {

}
