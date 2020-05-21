#include "viewmeeting.h"
#include "Model/Hierarchy/meeting.h"




ViewMeeting::ViewMeeting(QWidget *parent) : ModView(parent)
{
    inizio= new QTimeEdit();
    fine= new QTimeEdit();
    start = new QLabel("Inizio");
    end = new QLabel("Fine");

    inizio->setEnabled(false);
    fine->setEnabled(false);

    mainLayout->addWidget(start);
    mainLayout->addWidget(inizio);
    mainLayout->addWidget(end);
    mainLayout->addWidget(fine);



}

ViewMeeting::~ViewMeeting()
{

}

void ViewMeeting::switchReadable()
{
    ModView::switchReadable();
    inizio->setEnabled(true);
    fine->setEnabled(true);

}

void ViewMeeting::pushSaves(Model::It it)
{
    ModView::pushSaves(it);

    Meeting* currEve = dynamic_cast<Meeting*>(&**it);

    currEve->setStartTime(inizio->time());
    currEve->setEndTime(fine->time());


}

void ViewMeeting::fillView(Model::It it)
{
    ModView::fillView(it);

    Meeting* currEve = dynamic_cast<Meeting*>(&**it);

    inizio->setTime(currEve->getStartTime());
    fine->setTime(currEve->getEndTime());



}
