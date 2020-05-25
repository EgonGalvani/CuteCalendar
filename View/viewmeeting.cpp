#include <stdexcept>

#include "viewmeeting.h"
#include "Model/Hierarchy/meeting.h"

ViewMeeting::ViewMeeting(QWidget *parent) : ModView(parent) {

    inizio= new QTimeEdit(this);
    fine= new QTimeEdit(this);
    emails = new QTextEdit(this);
    alert = new QTimeEdit(this);
    checkRep= new QCheckBox(this);

    emailLabel= new QLabel("Emails");
    alertL= new QLabel("Alert");
    start = new QLabel("Inizio");
    end = new QLabel("Fine");
    rep = new QLabel("Ripeti");

    mainLayout->addWidget(start);
    mainLayout->addWidget(inizio);
    mainLayout->addWidget(end);
    mainLayout->addWidget(fine);
    mainLayout->addWidget(alertL);
    mainLayout->addWidget(alert);
}

void ViewMeeting::setEnabled(bool b) {
    ModView::setEnabled(b);
    emails->setReadOnly(!b);
    inizio->setEnabled(b);
    fine->setEnabled(b);
    alert->setEnabled(b);
    checkRep->setEnabled(b);
}

void ViewMeeting::pushSaves(Model::It it) {
    ModView::pushSaves(it);

    Meeting* currEve = dynamic_cast<Meeting*>(&**it);
    if(currEve) {
        currEve->setStartTime(inizio->time());
        currEve->setEndTime(fine->time());
        currEve->setAlertTime(alert->time());
        currEve->setRepeat(checkRep->isChecked());

        //Conversione EditText -> vector
    } else
        throw std::logic_error("Tipo errato per la modifica di una view meeting");
}

void ViewMeeting::fillView(Model::It it) {
    ModView::fillView(it);

    Meeting* currEve = dynamic_cast<Meeting*>(&**it);
    if(currEve) {
        inizio->setTime(currEve->getStartTime());
        fine->setTime(currEve->getEndTime());
        alert->setTime(currEve->getAlertTime());
        checkRep->setChecked(currEve->doesRepeat());
        //conversione vector-> EditText

    } else
        throw std::logic_error("Tipo errato per essere mostrato in una view meeting");
}

Meeting *ViewMeeting::createEvent()
{
    //manca emails e data
    Meeting* ritorno = new Meeting(checkTag->getTags(),inizio->time(),fine->time(), alert->time() , checkRep->isChecked() , txtNome->text().toStdString(),txtDesc->toPlainText().toStdString(),txtLuogo->text().toStdString(),Date(12,12,2000),checkTag->getTags());
    return ritorno;
}
