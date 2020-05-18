#include "viewmeeting.h"
#include "Model/Hierarchy/meeting.h"



void ViewMeeting::modifyPushed()
{
    ModView::modifyPushed();
    inizio->setEnabled(true);
    fine->setEnabled(true);

}

void ViewMeeting::confirmPushed()
{
    Meeting* currEve = dynamic_cast<Meeting*>(&**it);

    currEve->setStartTime(inizio->time());
    currEve->setEndTime(fine->time());

    ModView::confirmPushed();


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


    getInfo();
    setLayout(mainLayout);
}

ViewMeeting::~ViewMeeting()
{

}

void ViewMeeting::getInfo()
{
    ModView::getInfo();
    Meeting* currEve = dynamic_cast<Meeting*>(&**it);
    inizio->setTime(currEve->getStartTime());
    fine->setTime(currEve->getEndTime());

}
