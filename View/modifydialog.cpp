#include <QMessageBox>
#include <stdexcept>

#include "modifydialog.h"

#include "../Model/Hierarchy/birthday.h"
#include "../Model/Hierarchy/meeting.h"
#include "../Model/Hierarchy/reminder.h"
#include "../Model/Hierarchy/todolist.h"
#include "../Model/Hierarchy/workout.h"

ModifyDialog::ModifyDialog(QDate date,const Model::It& it, QDialog *parent)
    :  QDialog(parent), it(it), modifyEnabled(false), date(date) {

    // init grafica
    layout= new QVBoxLayout;
    viewLayout= new QVBoxLayout;
    buttomLayout = new QHBoxLayout;

    completato = new QLabel("Completato",this);
    btnDelete = new QPushButton(tr("Delete"),this);
    btnModify = new QPushButton(tr("Modify"),this);

    //Serie di if che controllano che tipo di view deve essere creata
    Event* currentEvent = &**it;
    if(dynamic_cast<Workout*>(currentEvent))
        view = new ViewAllenamento(this);
    else if(dynamic_cast<BirthDay*>(currentEvent))
        view = new ViewCompleanno(this);
    else if(dynamic_cast<Reminder*>(currentEvent))
        view = new ViewPromemoria(this);
    else if(dynamic_cast<Meeting*>(currentEvent))
        view = new ViewMeeting(this);
    else if(dynamic_cast<ToDoList*>(currentEvent))
        view = new ViewToDoList(this);
    else
        throw std::runtime_error("Il tipo considerato non rappresenta un evento valido");

    //Aggiunta di Label "Completato"
    completato->setAlignment(Qt::AlignCenter);
    viewLayout->addWidget(completato);
    viewLayout->addWidget(view);

    view->fillView(it); //Recupero dei dati dal Model

    //Controllo se l'evento è completato
    if((*it)->isCompleted()) {
        completato->setText("Completato");
        completato->setStyleSheet("QLabel { color: #fff; padding: 4px; background-color : green;}");
    } else {
        completato->setText("Non completato");
        completato->setStyleSheet("QLabel { color: #fff; padding: 4px; color: #fff; background-color : red;}");
    }
    view->setEnabled(false);

    buttomLayout->addWidget(btnDelete);
    buttomLayout->addWidget(btnModify);

    //connects signal di bottone cliccato con gli SLOT opportuni
    connect(btnModify, SIGNAL(clicked()), this, SLOT(modifyPushed()));
    connect(btnDelete, SIGNAL(clicked()), this, SLOT(deletePushed()));

    layout->addLayout(viewLayout);
    layout->addLayout(buttomLayout);

    setLayout(layout);
    setMinimumSize(200,600);
}



//Set dei parametri della view come modificabili e cambio dell'etichetta del bottone da "Modify" a "Confirm". Nel caso venga ripremuto pusha i salvataggi al model.
void ModifyDialog::modifyPushed() {
    if(!modifyEnabled) {
        view->setEnabled(true);
        btnModify->setText("Confirm");
        btnModify->setFocus();
        modifyEnabled = true;
    } else {
        try {
            view->pushSaves(it);
            QMessageBox::information(this, QString("Successo"), QString("Le modifiche sono state apportate con successo"));
            emit modifiedEvent(it);
            close();
        } catch(...) {
            QMessageBox::critical(this, QString("Error"), QString("Si sono riscontrati dei problemi durante il salvataggio delle modifiche..."));
        }
    }
}

//Cancellazione dell'evento
void ModifyDialog::deletePushed() {
    //emetto un signal di eliminazione
    emit deleteEvent(it);

    // chiudo il dialog
    close();
}
