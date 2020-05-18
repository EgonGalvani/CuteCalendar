#include "viewcompleanno.h"



void ViewCompleanno::modifyPushed()
{
    ModView::modifyPushed();
}

void ViewCompleanno::confirmPushed()
{

}

void ViewCompleanno::deletePushed()
{

}

ViewCompleanno::ViewCompleanno(const Model::It& it,QDialog *parent) : ModView(it,parent)
{
    setLayout(mainLayout);
}

ViewCompleanno::~ViewCompleanno()
{

}

void ViewCompleanno::getInfo()
{
    ModView::getInfo();


}
