#include "neweventdialog.h"
#include "tagpicker.h"

#include "viewworkout.h"
#include "viewbirthday.h"
#include "viewmeeting.h"
#include "viewreminder.h"
#include "viewtodolist.h"

NewEventDialog::NewEventDialog(QDate date,QDialog *parent) : QDialog(parent), date(date) {
    //init grafica
    mainLayout = new QVBoxLayout();
    selLayout = new QVBoxLayout();
    eventLayout = new QVBoxLayout();

    mainLayout->setAlignment(Qt::AlignTop);
    initComboBox();

    setLayout(mainLayout);
    setMinimumSize(200,700);
}


// Funzione che cancella tutti gli elementi di un layout.
void NewEventDialog::deleteLayout(QLayout* layout) {
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

//Funzione che crea la Combobox e la aggiunge al Layout.
void NewEventDialog::initComboBox() {
    selEvento = new QComboBox();
    selEvento->addItem("Allenamento");
    selEvento->addItem("Compleanno");
    selEvento->addItem("Meeting");
    selEvento->addItem("Promemoria");
    selEvento->addItem("Todo List");

    connect(selEvento, SIGNAL(currentIndexChanged(int)), this , SLOT(changedSel(int)) );

    selLayout->setAlignment(Qt::AlignTop);
    selLayout->addWidget(selEvento);
    mainLayout->addLayout(selLayout);
    mainLayout->addLayout(eventLayout);

    selEvento->setCurrentIndex(0);
    changedSel(0);
}

//Funzione che riconosce il tipo di view da instanziare
void NewEventDialog::changedSel(int index) {
    deleteLayout(eventLayout);

    switch(index){
        case 0:
            view = new ViewAllenamento(this);
            break;
        case 1:
            view = new ViewCompleanno(this);
            break;
        case 2:
            view = new ViewMeeting(this);
            break;
        case 3:
            view = new ViewPromemoria(this);
            break;
        case 4:
            view = new ViewToDoList(this);
    }

    eventLayout->addWidget(view);
    QPushButton* addEvent= new QPushButton(tr("Aggiungi Evento"));
    connect(addEvent,SIGNAL(clicked(bool)),this, SLOT(addPushed()));
    eventLayout->addWidget(addEvent);
}


//Slot che riconosce che il pulsante è stato premuto e quindi cerca di aggiungere l'evento
void NewEventDialog::addPushed() {
    try {
        emit newEventCreated(view->createEvent(date));
        QMessageBox::information(this, QString("Successo"), QString("L'inserimento ha avuto successo"));
        close();
    } catch(std::exception& e) {
        QMessageBox::critical(this, QString("Error"), QString::fromStdString(e.what()));
    }
}
