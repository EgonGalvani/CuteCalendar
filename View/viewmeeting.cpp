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


    setLayout(mainLayout);
}

ViewMeeting::~ViewMeeting()
{

}

