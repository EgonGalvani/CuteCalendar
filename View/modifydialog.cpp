#include "modifydialog.h"

ModifyDialog::ModifyDialog(const Model::It& it,int x,QDialog *parent) :  QDialog(parent), it(it)
{
    layout= new QVBoxLayout(this);
    viewLayout= new QVBoxLayout();
    buttomLayout = new QHBoxLayout();


    btnDelete = new QPushButton(tr("Delete"));
    btnModify = new QPushButton(tr("Modify"));
    btnConfirm = new QPushButton(tr("Confirm"));

    btnConfirm->setEnabled(false);


    switch (x) {
    case 1:
        view = new ViewCompleanno();
        break;
    case 2:
        view = new ViewMeeting();
    case 3:
        view= new ViewPromemoria();
    case 4:
        //todolist
        break;
    case 5:
        view = new ViewAllenamento();
    }



    viewLayout->addWidget(view);
    getInfo(it);


    buttomLayout->addWidget(btnDelete);
    buttomLayout->addWidget(btnModify);
    buttomLayout->addWidget(btnConfirm);

    //connects
    connect(btnModify, SIGNAL(clicked()), this, SLOT(modifyPushed()));
    connect(btnDelete, SIGNAL(clicked()), this, SLOT(deletePushed()));
    connect(btnConfirm, SIGNAL(clicked()), this, SLOT(confirmPushed()));



    layout->addLayout(viewLayout);
    layout->addLayout(buttomLayout);

    setLayout(layout);




}

ModifyDialog::~ModifyDialog()
{

}

void ModifyDialog::modifyPushed()
{
        view->switchReadable();
        btnConfirm->setEnabled(true);

}

void ModifyDialog::confirmPushed()
{

    view->pushSaves(it);
    close();


}

void ModifyDialog::deletePushed()
{

    //emetto un signal di eliminazione
      emit deleteEvent(it);

      // chiudo il dialog
      close();



}

void ModifyDialog::getInfo(Model::It it)
{
    view->fillView(it);

}
