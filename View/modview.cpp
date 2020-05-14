#include "modview.h"

ModView::ModView(QWidget *parent) : QWidget(parent)
{
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

   btnConfirm->setHidden(true);


   //connects

   connect(btnDelete, SIGNAL(clicked(true)), this , SLOT(deletePushed()));
   connect(btnModify, SIGNAL(clicked(true)), this, SLOT(modifyPushed()));
   connect(btnConfirm,SIGNAL(clicked(true)), this, SLOT(confirmPushed()));

   getInfo();



}

void ModView::modifyPushed()
{
    txtDesc->setEnabled(true);
    txtNome->setEnabled(true);
    txtLuogo->setEnabled(true);

    checkTag->setEnabled(true);

    btnConfirm->setHidden(false);


}

void ModView::confirmPushed()
{

}

void ModView::deletePushed()
{

}

void ModView::getInfo()
{

}
