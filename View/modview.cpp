#include "modview.h"

#include "tagpicker.h"

ModView::ModView(QWidget *parent) : QWidget(parent){

    mainLayout = new QVBoxLayout(this);



    lTag = new QLabel("Tag");
    lNome= new QLabel("Nome");
    lDesc= new QLabel("Descrizione");
    lLuogo = new QLabel("Luogo");

    txtDesc = new QTextEdit();
    txtNome = new QTextEdit();
    txtLuogo = new QTextEdit();
    checkTag= new QCheckBox();


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
        checkTag->setEnabled(false);


}

ModView::~ModView() {}


