#include "modview.h"


ModView::ModView(const Model::It& it, QDialog *parent) : QDialog(parent), it(it){

    mainLayout = new QVBoxLayout(this);
    editLayout = new QVBoxLayout();
    buttomLayout = new QHBoxLayout();

    lTag = new QLabel("Tag");
    lNome= new QLabel("Nome");
    lDesc= new QLabel("Descrizione");
    lLuogo = new QLabel("Luogo");

    txtDesc = new QTextEdit();
    txtNome = new QTextEdit();
    txtLuogo = new QTextEdit();

    checkTag= new QCheckBox();

    btnDelete = new QPushButton(tr("Delete"));
    btnModify = new QPushButton(tr("Modify"));
    btnConfirm= new QPushButton(tr("Confirm"));

    txtDesc->setEnabled(false);
    txtNome->setEnabled(false);
    txtLuogo->setEnabled(false);
    checkTag->setEnabled(false);
    btnConfirm->setEnabled(false);

    editLayout->addWidget(lNome);
    editLayout->addWidget(txtNome);
    editLayout->addWidget(lLuogo);
    editLayout->addWidget(txtLuogo);
    editLayout->addWidget(lDesc);
    editLayout->addWidget(txtDesc);
    editLayout->addWidget(lTag);
    editLayout->addWidget(checkTag);

    buttomLayout->addWidget(btnDelete);
    buttomLayout->addWidget(btnModify);
    buttomLayout->addWidget(btnConfirm);

    //connects
    connect(btnModify, SIGNAL(clicked()), this, SLOT(modifyPushed()));
    connect(btnDelete, SIGNAL(clicked()), this, SLOT(deletePushed()));
    connect(btnConfirm, SIGNAL(clicked()), this, SLOT(confirmPushed()));

    mainLayout->addLayout(editLayout);
    mainLayout->addLayout(buttomLayout);

    // setLayout(mainLayout);
    setMinimumSize(500, 500);
}

ModView::~ModView() {}

void ModView::modifyPushed() {
    // rendo tutti i campi editabili
    txtDesc->setEnabled(true);
    txtNome->setEnabled(true);
    txtLuogo->setEnabled(true);
    checkTag->setEnabled(true);
    btnConfirm->setEnabled(true);
}

void ModView::confirmPushed() {
    // applicare modifiche all'elemento corrente

    // chiudo il dialog
    close();
}

void ModView::deletePushed() {
    // emetto un signal di eliminazione
    emit deleteEvent(it);

    // chiudo il dialog
    close();
}

void ModView::getInfo() {
  txtDesc->setText(QString::fromStdString((*it)->getDesc()));
  txtNome->setText(QString::fromStdString((*it)->getName()));
  txtLuogo->setText(QString::fromStdString((*it)->getPlace()));
    // TAG BOH ***

}
