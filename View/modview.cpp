#include "modview.h"



ModView::ModView(QWidget *parent) : QWidget(parent){

    mainLayout = new QVBoxLayout(this);



    lTag = new QLabel("Tag");
    lNome= new QLabel("Nome");
    lDesc= new QLabel("Descrizione");
    lLuogo = new QLabel("Luogo");

    txtDesc = new QTextEdit();
    txtNome = new QTextEdit();
    txtLuogo = new QTextEdit();
    checkTag= new TagPicker();


    txtDesc->setReadOnly(true);
    txtNome->setReadOnly(true);
    txtLuogo->setReadOnly(true);

    checkTag->setEnabled(false);

    mainLayout->addWidget(lNome);
    mainLayout->addWidget(txtNome);
    mainLayout->addWidget(lLuogo);
    mainLayout->addWidget(txtLuogo);
    mainLayout->addWidget(lDesc);
    mainLayout->addWidget(txtDesc);
    mainLayout->addWidget(lTag);
    mainLayout->addWidget(checkTag);





}

void ModView::switchReadable()
{

        txtDesc->setReadOnly(false);
        txtNome->setReadOnly(false);
        txtLuogo->setReadOnly(false);
        checkTag->setEnabled(true);


}

void ModView::pushSaves(Model::It it)
{
    (*it)->setDesc((txtDesc->toPlainText()).toStdString());

    (*it)->setName((txtNome->toPlainText()).toStdString());

    (*it)->setPlace((txtLuogo->toPlainText()).toStdString());


}

void ModView::fillView(Model::It it)
{
    txtDesc->setText(QString::fromStdString((*it)->getDesc()));
    txtNome->setText(QString::fromStdString((*it)->getName()));
    txtLuogo->setText(QString::fromStdString((*it)->getPlace()));

}

ModView::~ModView() {}


