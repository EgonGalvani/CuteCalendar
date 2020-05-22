#include "newevent.h"
#include "tagpicker.h"

NewEvent::NewEvent(QDialog *parent) : QDialog(parent) {
    mainLayout = new QVBoxLayout();
    selLayout = new QVBoxLayout();
    eventLayout = new QVBoxLayout();

    mainLayout->setAlignment(Qt::AlignTop);
    initComboBox();

    setLayout(mainLayout);
}

void NewEvent::deleteLayout(QLayout* layout) {
    QLayoutItem* child;

    while(layout->count() > 0) {
        child = eventLayout->takeAt(0);

        if (child->layout() != 0)
            deleteLayout(child->layout());
        else if (child->widget() != 0)
            delete child->widget();

        delete child;
    }
}

void NewEvent::initComboBox() {
    selEvento = new QComboBox();
    selEvento->addItem("Allenamento");
    selEvento->addItem("Compleanno");
    selEvento->addItem("Meeting");
    selEvento->addItem("Promemoria");

    connect(selEvento, SIGNAL(currentIndexChanged(int)), this , SLOT(changedSel(int)) );

    selLayout->setAlignment(Qt::AlignTop);
    selLayout->addWidget(selEvento);



    mainLayout->addLayout(selLayout);
    mainLayout->addLayout(eventLayout);


    initAllenamento(); // scelta di default
}

void NewEvent::initAllenamento() {
   deleteLayout(eventLayout);
   // Possibile memory leak DA RISOLVERE
   view = new ViewAllenamento(this);

   eventLayout->addWidget(view);
   //TRovare modo più bello per non ripetere codice
   QPushButton* addEvent= new QPushButton(tr("Aggiungi Evento"));
   connect(addEvent,SIGNAL(clicked(bool)),this, SLOT(addPushed()));
   eventLayout->addWidget(addEvent);


}

void NewEvent::initCompleanno() {

    deleteLayout(eventLayout);
    // Possibile memory leak DA RISOLVERE
    view = new ViewCompleanno(this);
    eventLayout->addWidget(view);
    //TRovare modo più bello per non ripetere codice
    QPushButton* addEvent= new QPushButton(tr("Aggiungi Evento"));
    connect(addEvent,SIGNAL(clicked(bool)),this, SLOT(addPushed()));
    eventLayout->addWidget(addEvent);

}

void NewEvent::initMeeting() {
    deleteLayout(eventLayout);
    // Possibile memory leak DA RISOLVERE
    view = new ViewMeeting(this);
    eventLayout->addWidget(view);
    //TRovare modo più bello per non ripetere codice
    QPushButton* addEvent= new QPushButton(tr("Aggiungi Evento"));
    connect(addEvent,SIGNAL(clicked(bool)),this, SLOT(addPushed()));
    eventLayout->addWidget(addEvent);
}

void NewEvent::initPromemoria() {

    deleteLayout(eventLayout);
    // Possibile memory leak DA RISOLVERE
    view = new ViewPromemoria(this);
    eventLayout->addWidget(view);
    //TRovare modo più bello per non ripetere codice
    QPushButton* addEvent= new QPushButton(tr("Aggiungi Evento"));
    connect(addEvent,SIGNAL(clicked(bool)),this, SLOT(addPushed()));
    eventLayout->addWidget(addEvent);

}

void NewEvent::changedSel(int index) {
    deleteLayout(eventLayout);

    switch(index){
        case 0:
           initAllenamento();
            break;
        case 1:
            initCompleanno();
            break;
        case 2:
            initMeeting();
            break;
        case 3:
            initPromemoria();
            break;
    }
}

void NewEvent::addPushed()
{
 std::cout<< "Bottone Premuto" << std::endl;
}
