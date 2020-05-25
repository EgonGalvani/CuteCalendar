#include <QMessageBox>
#include <stdexcept>

#include "modifydialog.h"

#include "../Model/Hierarchy/birthday.h"
#include "../Model/Hierarchy/meeting.h"
#include "../Model/Hierarchy/reminder.h"
#include "../Model/Hierarchy/todolist.h"
#include "../Model/Hierarchy/workout.h"

#include "viewworkout.h"
#include "viewbirthday.h"
#include "viewmeeting.h"
#include "viewtodolist.h"
#include "viewreminder.h"

ModifyDialog::ModifyDialog(QDate date,const Model::It& it, QDialog *parent)
    :  QDialog(parent), it(it), modifyEnabled(false) {

    layout= new QVBoxLayout(this);
    viewLayout= new QVBoxLayout();
    buttomLayout = new QHBoxLayout();

    btnDelete = new QPushButton(tr("Delete"));
    btnModify = new QPushButton(tr("Modify"));

    Event* currentEvent = &**it;
    if(dynamic_cast<Workout*>(currentEvent))
        view = new ViewAllenamento(date,this);
    else if(dynamic_cast<BirthDay*>(currentEvent))
        view = new ViewCompleanno(date,this);
    else if(dynamic_cast<Reminder*>(currentEvent))
        view = new ViewPromemoria(date,this);
    else if(dynamic_cast<Meeting*>(currentEvent))
        view = new ViewMeeting(date,this);
    else if(dynamic_cast<ToDoList*>(currentEvent))
        view = new ViewToDoList(date,this);
    else
        throw std::runtime_error("Il tipo considerato non rappresenta un evento valido");

    viewLayout->addWidget(view);
    view->fillView(it);
    view->setEnabled(false);

    buttomLayout->addWidget(btnDelete);
    buttomLayout->addWidget(btnModify);

    //connects
    connect(btnModify, SIGNAL(clicked()), this, SLOT(modifyPushed()));
    connect(btnDelete, SIGNAL(clicked()), this, SLOT(deletePushed()));

    layout->addLayout(viewLayout);
    layout->addLayout(buttomLayout);

    setLayout(layout);
}

void ModifyDialog::modifyPushed() {
    if(!modifyEnabled) {
        view->setEnabled(true);
        btnModify->setText("Confirm");
        modifyEnabled = true;
    } else {
        try {
            view->pushSaves(it);
            QMessageBox::information(this, QString("Successo"), QString("Le modifiche sono state apportate con successo"));
        } catch(...) {
            QMessageBox::critical(this, QString("Error"), QString("Si sono riscontrati dei problemi durante il salvataggio delle modifiche..."));
        }

        close();
    }
}

void ModifyDialog::deletePushed() {
    //emetto un signal di eliminazione
    emit deleteEvent(it);

    // chiudo il dialog
    close();
}
