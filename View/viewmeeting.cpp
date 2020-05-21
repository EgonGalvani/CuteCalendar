#include <stdexcept>

#include "viewmeeting.h"
#include "Model/Hierarchy/meeting.h"

ViewMeeting::ViewMeeting(QWidget *parent) : ModView(parent) {

    inizio= new QTimeEdit();
    fine= new QTimeEdit();
    start = new QLabel("Inizio");
    end = new QLabel("Fine");

    mainLayout->addWidget(start);
    mainLayout->addWidget(inizio);
    mainLayout->addWidget(end);
    mainLayout->addWidget(fine);
}

void ViewMeeting::setEnabled(bool b) {
    ModView::setEnabled(b);
    inizio->setEnabled(b);
    fine->setEnabled(b);
}

void ViewMeeting::pushSaves(Model::It it) {
    ModView::pushSaves(it);

    Meeting* currEve = dynamic_cast<Meeting*>(&**it);
    if(currEve) {
        currEve->setStartTime(inizio->time());
        currEve->setEndTime(fine->time());
    } else
        throw std::logic_error("Tipo errato per la modifica di una view meeting");
}

void ViewMeeting::fillView(Model::It it) {
    ModView::fillView(it);

    Meeting* currEve = dynamic_cast<Meeting*>(&**it);
    if(!currEve) {
        inizio->setTime(currEve->getStartTime());
        fine->setTime(currEve->getEndTime());
    } else
        throw std::logic_error("Tipo errato per essere mostrato in una view meeting");
}
