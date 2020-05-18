#include "viewcompleanno.h"



void ViewCompleanno::modifyPushed()
{
    ModView::modifyPushed();
}

void ViewCompleanno::confirmPushed()
{
    ModView::confirmPushed();
}



ViewCompleanno::ViewCompleanno(const Model::It& it,QDialog *parent) : ModView(it,parent)
{
    getInfo();
    setLayout(mainLayout);
}

ViewCompleanno::~ViewCompleanno()
{

}

void ViewCompleanno::getInfo()
{
    ModView::getInfo();


}
