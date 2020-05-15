#include "viewmeeting.h"



void ViewMeeting::modifyPushed()
{
    ModView::modifyPushed();
    inizio->setEnabled(true);
    fine->setEnabled(true);

}

void ViewMeeting::confirmPushed()
{

}

void ViewMeeting::deletePushed()
{

}

ViewMeeting::ViewMeeting(const Model::It& it,QDialog *parent) : ModView(it,parent)
{
    inizio= new QTimeEdit();
    fine= new QTimeEdit();
    start = new QLabel("Inizio");
    end = new QLabel("Fine");

    inizio->setEnabled(false);
    fine->setEnabled(false);

    editLayout->addWidget(start);
    editLayout->addWidget(inizio);
    editLayout->addWidget(end);
    editLayout->addWidget(fine);



    setLayout(mainLayout);
}

ViewMeeting::~ViewMeeting()
{

}

void ViewMeeting::getInfo()
{

}
