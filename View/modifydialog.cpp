#include "modifydialog.h"

ModifyDialog::ModifyDialog(const Model::It &, QDialog *parent) :  QDialog(parent), it(it)
{
    layout= new QVBoxLayout(this);
    viewLayout= new QVBoxLayout();
    buttomLayout = new QHBoxLayout();


    btnDelete = new QPushButton(tr("Delete"));
    btnModify = new QPushButton(tr("Modify"));
    btnConfirm = new QPushButton(tr("Confirm"));

    btnConfirm->setEnabled(false);



    view= new ViewAllenamento();

    viewLayout->addWidget(view);


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
    /**  //applicare modifiche all'elemento corrente
    (*it)->setDesc((txtDesc->toPlainText()).toStdString());
    txtDesc->toPlainText();
    (*it)->setName((txtNome->toPlainText()).toStdString());
    txtNome->toPlainText();
    (*it)->setPlace((txtLuogo->toPlainText()).toStdString());
    txtLuogo->toPlainText();

    close();

**/

}

void ModifyDialog::deletePushed()
{

    //emetto un signal di eliminazione
      emit deleteEvent(it);

      // chiudo il dialog
      close();



}

void ModifyDialog::getInfo()
{
    /**
    txtDesc->setText(QString::fromStdString((*it)->getDesc()));
    txtNome->setText(QString::fromStdString((*it)->getName()));
    txtLuogo->setText(QString::fromStdString((*it)->getPlace()));
      // TAG BOH ***
  **/

}
